//
//  inputModule.h
//  CubeViewer
//
//  Created by Renato Pajarola.
//
//

#ifndef INPUTMODULE_H
#define INPUTMODULE_H

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

#include <vmmlib/matrix.hpp>

using namespace vmml;

// set initial viewer position and model transformation parameters
#define OFFSET -5.0
#define ANGLE_X  25
#define ANGLE_Y -25

// this must be packed/padded accordingly for a uniform shader block
typedef struct {
  GLuint wire;
} RenderSettings;


#ifdef __cplusplus
extern "C" {
#endif
  
  void readKeyboard(GLFWwindow* window, unsigned int keyUTF32);

#ifdef __cplusplus
}
#endif

#endif /* defined(INPUTMODULE_H) */









