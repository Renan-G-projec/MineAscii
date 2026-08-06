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

float rot = 0.f;

int8_t engine_init(void) {
    if (!glfwInit()) {
        printf("Error initializing GLFW.\nExiting...\n");
        return 0;
    };

    GLFWwindow* window = glfwCreateWindow(100, 100, "Hello, window! - AMDG", NULL, NULL);

    glfwMakeContextCurrent(window);
    gladLoadGL();

    Mesh square = mesh_init(vertices, indices, sizeof(vertices), sizeof(indices));

    Shader sh = shader_create("./assets/shaders/main.vert", "./assets/shaders/main.frag");
    shader_bind(sh);
    
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

        mesh_draw(&square);
        glfwSwapBuffers(window);

        rot += 0.1;
        if (rot > 359) rot = 0;
    }

    shader_destroy(sh);
    mesh_destroy(&square);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}