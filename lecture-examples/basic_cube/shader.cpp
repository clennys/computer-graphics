//
//  shader.cpp
//  CubeViewer
//
//  Created by Renato Pajarola.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

// may be needed, e.g. on Linux and Windows
//#define GLEW
#ifdef GLEW
  #include <GL/glew.h>
#endif

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

#include "shader.h"


GLuint getShader(const char *filename, bool type)
{
  char *shadertext = NULL;
  GLuint shader;

  if (type)
	shader = glCreateShader(GL_VERTEX_SHADER);
  else
	shader = glCreateShader(GL_FRAGMENT_SHADER);

  shadertext = readShaderText(filename);
  glShaderSource(shader, 1, (const char**)&shadertext, 0);
  free(shadertext);
  
  glCompileShader(shader);
  return shader;
}


char* readShaderText(const char *filename)
{
  FILE *in;
  char *shaderSrc = NULL;

  // open shader file
  if (!(in = fopen(filename, "r"))) {
	fprintf(stderr, "Cannot open input file %s.\n", filename);
	exit(1);
  }
  struct stat st;
  stat(filename, &st);
  shaderSrc = (char*)calloc(st.st_size+1, sizeof(char));  // +1 for NULL terminated string
  
  // load shader source
  if (fread(shaderSrc, sizeof(char), st.st_size, in) != st.st_size*sizeof(char)) {
	fprintf(stderr, "Cannot read %d characters from input file %s.\n", (int)st.st_size, filename);
	exit(1);
  }
  fclose(in);

  return shaderSrc;
}
