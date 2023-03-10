//
//  main.cpp
//  CubeViewer
//
//  Created by Renato Pajarola.
//
//

#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// may be needed, e.g. on Linux and Windows
#define GLEW
#ifdef GLEW
#include <GL/glew.h>
#endif

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

#include "cube.h"
#include "inputModule.h"
#include "shader.h"

#include <vmmlib/matrix.hpp>
#include <vmmlib/vector.hpp>

using namespace vmml;

// window settings
GLFWwindow *window;
int screenWidth = 512;
int screenHeight = 512;
int windowWidth = screenWidth;
int windowHeight = screenHeight;

static int frames = 0;

// rendering settings
extern RenderSettings settings;

// light and color parameters
vec4f black_color(0.2, 0.2, 0.2, 1.0);
vec4f line_color(1.0, 0.0, 0.6, 1.0);

// model-view and projection matrices
mat4f viewMatrix, projMatrix;

struct {
  float fieldOfView;
  float aspect;
  float nearPlane;
  float farPlane;
} pD;

// vertex attributes, uniform variables, blocks and shader indices
GLuint vertexLoc = 0, colorLoc = 1, normalLoc = 2;
GLuint projMatrixLoc, viewMatrixLoc, extColorLoc;
GLuint shaderProgram, settingsBO;

void cleanup(int sig) {
  // insert cleanup code here (i.e. deleting structures or so)
  fprintf(stderr, "%d frames drawn.\n", frames);
  exit(0);
}

void buildProjectionMatrix(float fov, float ratio, float nearP, float farP) {
  float f = 1.0f / tan(fov * (M_PI / 360.0));

  projMatrix = mat4f::IDENTITY;

  projMatrix[0][0] = f / ratio;
  projMatrix[1][1] = f;
  projMatrix[2][2] = (farP + nearP) / (nearP - farP);
  projMatrix[2][3] = (2.0f * farP * nearP) / (nearP - farP);
  projMatrix[3][2] = -1.0f;
  projMatrix[3][3] = 0.0f;
}

// ##########################################3
//  OpenGL Display function
//
void render(void) {
  frames++;

  assert(window);
  glfwMakeContextCurrent(window);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // set initial viewer position and model transformation
  viewMatrix = mat4f::IDENTITY;
  viewMatrix.set_column(3, vec4f(0.0, 0.0, OFFSET, 1.0));
  viewMatrix.rotate_x(ANGLE_X / 180.0 * M_PI);
  viewMatrix.rotate_y(ANGLE_Y / 180.0 * M_PI);

  // activate shader programs
  glUseProgram(shaderProgram);

  // load matrices into uniform shader variables
  glUniformMatrix4fv(projMatrixLoc, 1, false, projMatrix);
  glUniformMatrix4fv(viewMatrixLoc, 1, false, viewMatrix);

  // set global color
  if (settings.wire)
    glUniform4fv(extColorLoc, 1, line_color);
  else
    glUniform4fv(extColorLoc, 1, black_color);

  // load render settings
  glBindBuffer(GL_UNIFORM_BUFFER, settingsBO);
  glBufferData(GL_UNIFORM_BUFFER, sizeof(settings), &settings, GL_DYNAMIC_DRAW);

  drawCube();
  glfwSwapBuffers(window);
}

// ##########################################
//  GLFW Reshape function
//
void reshape(GLFWwindow *window, int width, int height) {
  assert(window);
  glfwGetWindowSize(window, &windowWidth, &windowHeight);

  screenWidth = width;
  screenHeight = height;

  if (screenWidth <= 0 || screenHeight <= 0)
    return;

  glViewport(0, 0, screenWidth, screenHeight);
  pD.aspect = (float)screenWidth / screenHeight;
  buildProjectionMatrix(pD.fieldOfView, pD.aspect, pD.nearPlane, pD.farPlane);
}

// ##########################################
//  Init GL display settings
//
void initDisplay() {
  // perspective projection parameters
  pD.fieldOfView = 45.0;
  pD.aspect = (float)screenWidth / screenHeight;
  pD.nearPlane = 0.1;
  pD.farPlane = 50.0;

  // setup initial projection and model matrices
  buildProjectionMatrix(pD.fieldOfView, pD.aspect, pD.nearPlane, pD.farPlane);
  viewMatrix = mat4f::IDENTITY;

  glEnable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  glClearColor(1.0, 1.0, 1.0, 1.0);
}

// ##########################################
//  Init OpenGL shaders
//
void initShaders() {
  GLuint v, f, settingsLoc;

  // initialize shaders and program
  v = getShader("./shader.vert", true);
  f = getShader("./shader.frag", false);

  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, v);
  glAttachShader(shaderProgram, f);

  // set shader input/output parameter locations
  glBindAttribLocation(shaderProgram, vertexLoc, "in_position");
  glBindAttribLocation(shaderProgram, colorLoc, "in_color");
  glBindAttribLocation(shaderProgram, normalLoc, "in_normal");
  glBindFragDataLocation(shaderProgram, 0, "f_color");

  glLinkProgram(shaderProgram);

  // get uniform data variables locations
  projMatrixLoc = glGetUniformLocation(shaderProgram, "projMatrix");
  viewMatrixLoc = glGetUniformLocation(shaderProgram, "viewMatrix");
  extColorLoc = glGetUniformLocation(shaderProgram, "ext_color");

  // setup render settings buffer
  glGenBuffers(1, &settingsBO);
  glBindBuffer(GL_UNIFORM_BUFFER, settingsBO);
  glBufferData(GL_UNIFORM_BUFFER, sizeof(settings), &settings, GL_DYNAMIC_DRAW);

  // the next 2 lines connect the uniform name and bufferobject to the same
  // index 0
  settingsLoc = glGetUniformBlockIndex(shaderProgram, "settingsBlock");
  glUniformBlockBinding(shaderProgram, settingsLoc, 0);
  glBindBufferBase(GL_UNIFORM_BUFFER, 0, settingsBO);
}

// ##########################################
//  Main function
//
int main(int argc, char **argv) {
  char cdir[128];

  // signal(SIGHUP, cleanup);

  fprintf(stderr, "\nPress h or H for help.\n\n");

  getcwd(cdir, 128);
  if (!glfwInit())
    return -1;
  chdir(cdir);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

  window =
      glfwCreateWindow(windowWidth, windowHeight, "Cube Viewer", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  } else {
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
  }
  glfwMakeContextCurrent(window);

  glfwSetFramebufferSizeCallback(window, reshape);
  glfwSetCharCallback(window, readKeyboard);

  fprintf(stderr, "OpenGL Version: %s\n", glGetString(GL_VERSION));

// may be needed, e.g. on Linux and Windows
#ifndef __APPLE__
  if (glewInit() != GLEW_OK)
    return -1;
#endif

  initDisplay();
  initShaders();
  initCube();

  // loop until the user closes the window
  while (!glfwWindowShouldClose(window)) {
    render();
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
