// Ad Maiorem Dei Gloriam!
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "asciibuffer.h"

// Vertices normalized


float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
}; 


const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";


int main() {
    if (!glfwInit()) {
        printf("Error initializing GLFW.\nExiting...\n");
        return 0;
    };

    GLFWwindow* window = glfwCreateWindow(100, 100, "Hello, window! - AMDG", NULL, NULL);

    glfwMakeContextCurrent(window);
    gladLoadGL();

    unsigned int vao;
    glGenVertexArrays(1, &vao);

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);

    unsigned int vtSh = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vtSh, 1, &vertexShaderSource, NULL);
    glCompileShader(vtSh);

    unsigned int fgSh = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fgSh, 1, &fragmentShaderSource, NULL);
    glCompileShader(fgSh);

    unsigned int Sh = glCreateProgram();
    glAttachShader(Sh, vtSh);
    glAttachShader(Sh, fgSh);
    glLinkProgram(Sh);

    glUseProgram(Sh);

    glDeleteShader(vtSh);
    glDeleteShader(fgSh);
    
    while (!glfwWindowShouldClose(window)) {
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}