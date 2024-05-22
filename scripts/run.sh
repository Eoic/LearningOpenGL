#!/bin/sh

# Create a build directory if it doesn't exist.
mkdir -p build

# Change to the build directory.
cd build || { echo "Failed to enter build directory."; exit 1; }

# Check if CMake is installed.
if ! command -v cmake > /dev/null 2>&1; then
    echo "CMake is not installed. Please install it and try again."
    exit 1
fi

# Run CMake to configure the project.
cmake ../ || { echo "CMake configuration failed."; exit 1; }

# Check if Make is installed.
if ! command -v make > /dev/null 2>&1; then
    echo "Make is not installed. Please install it and try again."
    exit 1
fi

# Build the project using Make.
make || { echo "Make build failed"; exit 1; }

printf %80s |tr " " "-";
echo;

# Execute the compiled binary.
if [ -x ./OpenGL ]; then
    ./OpenGL
else
    echo "Executable ./OpenGL binary is not found or is not an executable."
    exit 1
fi
