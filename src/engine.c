// Ad Maiorem Dei Gloriam!

#include "engine.h"

float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

int8_t engine_init(void) {
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

    GLuint ebo = ebo_create();
    ebo_bind(ebo);
    ebo_send_data(ebo, sizeof(indices), indices);

    vao_define(0, 3, GL_FLOAT, 3 * sizeof(float), NULL);

    Shader sh = shader_create("./assets/shaders/main.vert", "./assets/shaders/main.frag");
    shader_bind(sh);
    
    while (!glfwWindowShouldClose(window)) {
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    shader_destroy(sh);
    vao_destroy(vao);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}