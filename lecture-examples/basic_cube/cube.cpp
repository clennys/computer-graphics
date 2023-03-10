//
//  cube.cpp
//  CubeViewer
//
//  Created by Renato Pajarola.
//
//

#include <stdlib.h>

// may be needed, e.g. on Linux and Windows
//#define GLEW
#ifdef GLEW
  #include <GL/glew.h>
#endif

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

#include "cube.h"
#include "inputModule.h"

// rendering settings
extern RenderSettings settings;

// array and buffor object IDs and indices
extern GLuint vertexLoc, colorLoc, normalLoc;

GLuint cubeVAO = 0;				  // vertex array object ID
GLuint vndBO = 0;				  // vertex index buffer ID
GLuint lndBO = 0;				  // line index buffer ID


static float cubeVertices[24][3] =
{
  {-1.0, -1.0, -1.0},  // index 0
  {-1.0, -1.0, 1.0},
  {-1.0, 1.0, 1.0},
  {-1.0, 1.0, -1.0},
  
  {1.0, 1.0, 1.0},    // index 4
  {1.0, -1.0, 1.0},
  {1.0, -1.0, -1.0},
  {1.0, 1.0, -1.0},
  
  {-1.0, -1.0, -1.0},  // index 8
  {1.0, -1.0, -1.0},
  {1.0, -1.0, 1.0},
  {-1.0, -1.0, 1.0},
  
  {1.0, 1.0, 1.0},    // index 12
  {1.0, 1.0, -1.0},
  {-1.0, 1.0, -1.0},
  {-1.0, 1.0, 1.0},
  
  {-1.0, -1.0, -1.0},  // index 16
  {-1.0, 1.0, -1.0},
  {1.0, 1.0, -1.0},
  {1.0, -1.0, -1.0},
  
  {1.0, 1.0, 1.0},    // index 20
  {-1.0, 1.0, 1.0},
  {-1.0, -1.0, 1.0},
  {1.0, -1.0, 1.0}
};

static float cubeColors[24][3] =
{
  {0.8, 0.8, 0.0},
  {0.8, 0.8, 0.0},
  {0.8, 0.8, 0.0},
  {0.8, 0.8, 0.0},
  
  {0.8, 0.0, 0.0},
  {0.8, 0.0, 0.0},
  {0.8, 0.0, 0.0},
  {0.8, 0.0, 0.0},
  
  {0.0, 0.8, 0.0},
  {0.0, 0.8, 0.0},
  {0.0, 0.8, 0.0},
  {0.0, 0.8, 0.0},
  
  {0.0, 0.0, 0.8},
  {0.0, 0.0, 0.8},
  {0.0, 0.0, 0.8},
  {0.0, 0.0, 0.8},
  
  {0.0, 0.8, 0.8},
  {0.0, 0.8, 0.8},
  {0.0, 0.8, 0.8},
  {0.0, 0.8, 0.8},
  
  {0.8, 0.0, 0.8},
  {0.8, 0.0, 0.8},
  {0.8, 0.0, 0.8},
  {0.8, 0.0, 0.8}
};

static float cubeNormals[24][3] =
{
  {-1.0, 0.0, 0.0},
  {-1.0, 0.0, 0.0},
  {-1.0, 0.0, 0.0},
  {-1.0, 0.0, 0.0},
  
  { 1.0, 0.0, 0.0},
  { 1.0, 0.0, 0.0},
  { 1.0, 0.0, 0.0},
  { 1.0, 0.0, 0.0},
  
  {0.0, -1.0, 0.0},
  {0.0, -1.0, 0.0},
  {0.0, -1.0, 0.0},
  {0.0, -1.0, 0.0},
  
  {0.0,  1.0, 0.0},
  {0.0,  1.0, 0.0},
  {0.0,  1.0, 0.0},
  {0.0,  1.0, 0.0},
  
  {0.0, 0.0, -1.0},
  {0.0, 0.0, -1.0},
  {0.0, 0.0, -1.0},
  {0.0, 0.0, -1.0},
  
  {0.0, 0.0,  1.0},
  {0.0, 0.0,  1.0},
  {0.0, 0.0,  1.0},
  {0.0, 0.0,  1.0}
};

static GLuint triangleIndices[36] =
{
   0, 1, 2,     2, 3, 0,
   4, 5, 6,     6, 7, 4,
   8, 9, 10,   10, 11, 8,
  12, 13, 14,  14, 15, 12,
  16, 17, 18,  18, 19, 16,
  20, 21, 22,  22, 23, 20
};

static GLuint lineIndices[24] =
{
  0, 1, 1, 2, 2, 3, 3, 0,
  4, 5, 5, 6, 6, 7, 7, 4,
  2, 4, 1, 5, 0, 6, 3, 7
};


void initCube()
{
  GLuint posBO = 0;
  GLuint colBO = 0;
  GLuint norBO = 0;

  // initialize cube's buffer objects
  glGenBuffers(1, &posBO);
  glBindBuffer(GL_ARRAY_BUFFER, posBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
  
  glGenBuffers(1, &colBO);
  glBindBuffer(GL_ARRAY_BUFFER, colBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cubeColors), cubeColors, GL_STATIC_DRAW);
  
  glGenBuffers(1, &norBO);
  glBindBuffer(GL_ARRAY_BUFFER, norBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cubeNormals), cubeNormals, GL_STATIC_DRAW);

  // initialize index buffers
  glGenBuffers(1, &vndBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vndBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangleIndices), triangleIndices, GL_STATIC_DRAW);

  glGenBuffers(1, &lndBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lndBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(lineIndices), lineIndices, GL_STATIC_DRAW);

  // initialize cube's vertex array object
  glGenVertexArrays(1, &cubeVAO);
  glBindVertexArray(cubeVAO);
  
  glBindBuffer(GL_ARRAY_BUFFER, posBO);
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);
  
  glBindBuffer(GL_ARRAY_BUFFER, colBO);
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

  glBindBuffer(GL_ARRAY_BUFFER, norBO);
  glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(normalLoc);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // can delete buffer objects ver/col/nor
  glDeleteBuffers(1,  &posBO);
  glDeleteBuffers(1,  &colBO);
  glDeleteBuffers(1,  &norBO);
}


void drawCube()
{
  glBindVertexArray(cubeVAO);
  
  if (!settings.wire) {
    // set polygon fill mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    // draw each cube face as an individual polygon
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vndBO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
  } else {
    // set antialiasingand wire-frame rendering mode
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    
    // set wire-frame rendering mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(1.0);
    
    // draw each cube face as an individual polygon
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lndBO);
    glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
    
    glDisable(GL_BLEND);
    glDisable(GL_LINE_SMOOTH);
  }
  
  glBindVertexArray(0);
}
