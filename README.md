# computer-graphics

## Summary

### What is OpenGL?
> OpenGL by itself is not an API, but merely a specification, developed and maintained by the Khronos Group. 
- The OpenGL specification specifies exactly what the result/output of each function should be and how it should perform. It is then up to the developers (graphics card manufacturers).

#### State Maschine
- OpenGL is by itself a large state machine: a collection of variables that define how OpenGL should currently operate.
	- State is reffered as __context__.
	- State is change by setting options, manipulating buffers and then render the context.

#### Objects
- An object in OpenGL is a collection of options that represents a subset of OpenGL's state.
```cpp
// The State of OpenGL
struct OpenGL_Context {
  	...
  	object_name* object_Window_Target;
  	...  	
};

// create object
unsigned int objectId = 0;
glGenObject(1, &objectId);
// bind/assign object to context
glBindObject(GL_WINDOW_TARGET, objectId);
// set options of object currently bound to GL_WINDOW_TARGET
glSetObjectOption(GL_WINDOW_TARGET, GL_OPTION_WINDOW_WIDTH,  800);
glSetObjectOption(GL_WINDOW_TARGET, GL_OPTION_WINDOW_HEIGHT, 600);
// set context target back to default
glBindObject(GL_WINDOW_TARGET, 0);
```

### Creating a window
- In order to create graphics we need to create an OpenGL context and application window, which is however not done by OpenGL and are specified by the operating system.
- OpenGL purposefully tries to abstract itself from these operations. There are luckaly quite a few libraries that provide the the functionality we need.

#### GLFW 
- GLFW is a library, written in C, specifically targeted at OpenGL
- GLFW gives us the bare necessities required for rendering goodies to the screen.
	- Allows us to create an OpenGL context, define window parameters, and handle user input
```cpp
#include <GLFW/glfw3.h>
```





