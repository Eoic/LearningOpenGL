#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

using std::cout, std::cerr, std::endl;

namespace fs = std::filesystem;

const GLint WIDTH = 800;
const GLint HEIGHT = 600;
const char* WINDOW_TITLE = "OpenGL";

GLuint VAO, VBO, shader;

std::string readFile(std::string path) {
    std::ifstream file(path, std::ios::in | std::ios::binary);
    const auto size = fs::file_size(path);
    std::string result(size, '\0');
    file.read(result.data(), size);
    return result;
}

void createTriangle() {
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void glfwErrorCallback(int error, const char* description) {
    cerr << "GLFW Error (" << error << "): " << description << endl;
}

int main() {
    glfwSetErrorCallback(glfwErrorCallback);

    if (!glfwInit()) {
        cerr << "Failed to initialize GLFW" << endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, WINDOW_TITLE, NULL, NULL);

    if (!window) {
        cerr << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        cerr << "Failed to initialize GLEW" << endl;
        return -1;
    }

    cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(3.0f, 0.8f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
