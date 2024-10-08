cmake_minimum_required(VERSION 3.28)
include(FetchContent)
project(OpenGL)
set(CMAKE_CXX_STANDARD 20)

# GLEW
set(BUILD_UTILS OFF CACHE BOOL "" FORCE)
add_subdirectory(vendor/glew/build/cmake) 

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(vendor/glfw)

include_directories(vendor/glew/include)
include_directories(vendor/glfw/include)

# GLM
FetchContent_Declare(
	glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG 	    0af55ccecd98d4e5a8d1fad7de25ba429d60e863
)

FetchContent_MakeAvailable(glm)

# Copy chaders into build folder.
add_custom_target(
    copy_assets
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/shaders
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shaders ${CMAKE_BINARY_DIR}/shaders
    COMMENT "Copying ${CMAKE_SOURCE_DIR}/shaders to ${CMAKE_BINARY_DIR}/shaders."
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_executable(OpenGL main.cpp)
target_link_libraries(OpenGL PRIVATE glew glfw glm::glm)
add_dependencies(OpenGL copy_assets)
