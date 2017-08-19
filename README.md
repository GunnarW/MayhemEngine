# MayhemEngine

### Needed Libraries
GLFW http://www.glfw.org/download.html
CMake https://cmake.org/download/
GLM http://glm.g-truc.net/

## Setup Instructions
This project is built using Visual Studio. 

1. Extract GLFW and GLM to an external includes folder.
2. Install CMake, Set the source code directory to GLFW's root directory. Set the build to be the GLFW's build folder. Got to the configure button, and select visual studio option.
3. In Visual Studio, open the project settings and go to the "VC++ Directories" page. In the "Include Directories" item, select <edit> and select the includes folder that you created in step 1. 
4. In Visual Studio's project settings, go to the "Linker/Input" page. Under the field "Additional Dependencies", hit the <edit> button and add opengl32.lib, and glfw3.lib.