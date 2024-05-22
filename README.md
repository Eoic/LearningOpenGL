# OpenGL starter project

### Features
* CMake configuration with GLEW and GLFW.
* Example code for creating a window using the mentioned libraries.
* Automatically download and unzip dependencies into dedicated directories.
* CMake plugin preset for VSCode.

### Usage
1. Run `./scripts/install-deps.sh` to download and unzip dependenciew into `vendor` directory.
2. Use `./scripts/run.sh` script to compile and run the project.
3. (Alternative) Use VSCode [CMake](https://marketplace.visualstudio.com/items?itemName=twxs.cmake) plugin to build and debug through the IDE.

### Issues
* Doesn't seem to work on Wayland.