// Ad Maiorem Dei Gloriam!

#include "engine.h"

float vertices[] = {
     0.5f,  0.5f, 1.0f,  // top right
     0.5f, -0.5f, 1.0f,  // bottom right
    -0.5f, -0.5f, 1.0f,  // bottom left
    -0.5f,  0.5f, 1.0f   // top left 
};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

void updateCameraInput(Camera* camera, KeyboardCtx *kb) {
    if (keyboardctx_isKeyPressed(kb, 'W')) {
        camera->position[2]++;
    }
    if (keyboardctx_isKeyPressed(kb, 'S')) {
        camera->position[2]--;
    }
    if (keyboardctx_isKeyPressed(kb, 'A')) {
        camera->position[0]++;
    }
    if (keyboardctx_isKeyPressed(kb, 'D')) {
        camera->position[0]--;
    }
}

int8_t engine_init(void) {
    if (!glfwInit()) {
        printf("Error initializing GLFW.\nExiting...\n");
        return 0;
    };

    GLFWwindow* window = glfwCreateWindow(100, 100, "Hello, window! - AMDG", NULL, NULL);

    glfwMakeContextCurrent(window);
    gladLoadGL();

    KeyboardCtx kb = keyboardctx_create();
    keyboardctx_bindwindowctx(&kb, window);

    Mesh square = mesh_init(vertices, indices, sizeof(vertices), sizeof(indices));

    Shader sh = shader_create("./assets/shaders/main.vert", "./assets/shaders/main.frag");
    shader_bind(sh);

    Camera cam = camera_create();
    
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

        updateCameraInput(&cam, &kb);
        camera_send_matrix(&cam, sh);

        mesh_draw(&square);
        glfwSwapBuffers(window);
    }

    shader_destroy(sh);
    mesh_destroy(&square);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}