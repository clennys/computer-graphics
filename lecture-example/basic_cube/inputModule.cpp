//
//  inputModule.cpp
//  CubeViewer
//
//  Created by Renato Pajarola.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <math.h>

#include "inputModule.h"


RenderSettings settings = {0};

void cleanup(int sig);
void reshape(GLFWwindow* window, int width, int height);


void readKeyboard(GLFWwindow* window, unsigned int keyUTF32)
{
  switch(keyUTF32){
	case 'h':
	case 'H':
	  printf("\tpress q/Q for quit\n");
	  printf("\tpress w to togle wire frame rendering\n");
	  break;
	case  0x1B:
	case  'q':
	case  'Q':
	  //kill(getpid(), SIGHUP); 
	  cleanup(0);
	  break;
	case 'w':
	  settings.wire = !settings.wire;
	  break;
	default:
	  break;
  }
}
