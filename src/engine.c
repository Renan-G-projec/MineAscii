// Ad Maiorem Dei Gloriam!

#include "engine.h"

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
}; 

int8_t engine_init() {
    if (!glfwInit()) {
        printf("Error initializing GLFW.\nExiting...\n");
        return 0;
    };

    GLFWwindow* window = glfwCreateWindow(100, 100, "Hello, window! - AMDG", NULL, NULL);

    glfwMakeContextCurrent(window);
    gladLoadGL();

    GLuint vao = vao_create();
    vao_bind(vao);

    GLuint vbo = vbo_create();
    vbo_bind(vbo);
    vbo_set_data(vbo, sizeof(vertices), vertices);

    vao_define(0, 3, GL_FLOAT, 3 * sizeof(float), NULL);

    Shader sh = shader_create("./assets/shaders/main.vert", "./assets/shaders/main.frag");
    shader_bind(sh);
    
    while (!glfwWindowShouldClose(window)) {
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    shader_destroy(sh);
    vao_destroy(vao);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}