Note that the location of the fragment and vertex shaders relative to the executable is hardcoded in the main.cpp file in the function initShaders().

You need the VMMLib library which you can clone from https://github.com/VMML/vmmlib.git

Make the vmmlib include path somewhere available, e.g. from your user's home as ~/include/vmmlib/ or similar and include it in the include path for compiling. It is a header template library so it does not need to be compiled and is not a binary library to be linked!


Basic minimal command line compilation, also including GLEW, then could be something like this:
c++ -std=c++11 -o cubeview *.cpp -I <include_path_for_vmmlib> -lGLEW -lglfw -lGL 


On MacOS, with VMMLib installed in the user's include directory, it may need include directories and libraries to be specified:
c++ -std=c++11 -o cubeview *.cpp -I ~/include/ -I /opt/homebrew/include -L /opt/homebrew/lib -lglfw -framework OpenGL -Wno-deprecated-declarations
