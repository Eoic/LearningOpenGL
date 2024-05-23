#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

using std::cout, std::cerr, std::endl;

namespace fs = std::filesystem;

const GLint WIDTH = 800;
const GLint HEIGHT = 600;
const char* WINDOW_TITLE = "OpenGL";

GLuint VAO, VBO, program;

const char* readFile(const std::string path) {
    std::ifstream file(path, std::ios::in | std::ios::binary | std::ios::ate);

    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << path << std::endl;
        return nullptr;
    }

    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    char* buffer = new char[fileSize + 1];
    file.read(buffer, fileSize);
    buffer[fileSize] = '\0';
    file.close();

    return buffer;
}

void attachShader(GLuint program, const std::string shaderPath, GLenum shaderType) {
    auto shaderCode = readFile(shaderPath);
    GLuint shader = glCreateShader(shaderType);

    const GLchar* code[1];
    code[0] = shaderCode;

    GLint length[1];
    length[0] = strlen(shaderCode);
    glShaderSource(shader, 1, code, length);
    glCompileShader(shader);

    GLint result = 0;
    GLchar errorLog[1024] = {0};

    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
 
    if (!result) {
        glGetShaderInfoLog(shader, sizeof(errorLog), NULL, errorLog);
        cerr << "Error compiling the shader " << shaderType << ": " << errorLog << endl;
        return;
    }

    glAttachShader(program, shader);
}

void compileShaders() {
    program = glCreateProgram();

    if (!program) {
        cerr << "Failed to create shader program!" << endl;
        return;
    }

    attachShader(program, "./shaders/triangle.vert", GL_VERTEX_SHADER);
    attachShader(program, "./shaders/triangle.frag", GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar errorLog[1024] = {0};

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &result);

    if (!result) {
        glGetProgramInfoLog(program, sizeof(errorLog), NULL, errorLog);
        cerr << "Error linking the program: " << errorLog << endl;
        return;
    }

    glValidateProgram(program);
    glGetProgramiv(program, GL_VALIDATE_STATUS, &result);

    if (!result) {
        glGetProgramInfoLog(program, sizeof(errorLog), NULL, errorLog);
        cerr << "Error validating the program: " << errorLog << endl;
        return;
    }
}

void createTriangle() {
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, WINDOW_TITLE, NULL, NULL);

    if (!window) {
        cerr << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);    
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        cerr << "Failed to initialize GLEW." << endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }

    glViewport(0, 0, bufferWidth, bufferHeight);

    createTriangle();
    compileShaders();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        glUseProgram(0);

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
