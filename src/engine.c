// Ad Maiorem Dei Gloriam!

#include "engine.h"

float vertices[] = {
    -1.0f, -1.0f, -1.0f, // front 
    -1.0f, 1.0f, -1.0f, // front
    1.0f, -1.0f, -1.0f, // front
    1.0f, 1.0f, -1.0f, // front
    -1.0f, -1.0f, 1.0f, // back
    -1.0f, 1.0f, 1.0f, // back
    1.0f, -1.0f, 1.0f, // back
    1.0f, 1.0f, 1.0f, // back
};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 2, // front face
    1, 3, 2, // front face
    1, 5, 7, // top face
    7, 3, 1, // top face
    4, 5, 6, // back face
    5, 7, 6 // back face
};

void updateCameraInput(Camera* camera, KeyboardCtx *kb) {
    
    if (keyboardctx_isKeyPressed(kb, 'W')) {
        glm_vec3_add(camera->orientation, camera->position, camera->position);
    }
    if (keyboardctx_isKeyPressed(kb, 'S')) {
        glm_vec3_negate(camera->orientation);
        glm_vec3_add(camera->orientation, camera->position, camera->position);
        glm_vec3_negate(camera->orientation);
    }
    if (keyboardctx_isKeyPressed(kb, 'A')) {
        vec3 horizontalAxis;
        glm_cross(camera->orientation, (vec3){0, 1, 0}, horizontalAxis);

        glm_vec3_negate(horizontalAxis);
        glm_vec3_add(horizontalAxis, camera->position, camera->position);
    }
    if (keyboardctx_isKeyPressed(kb, 'D')) {
        vec3 horizontalAxis;
        glm_cross(camera->orientation, (vec3){0, 1, 0}, horizontalAxis);
        
        glm_vec3_add(horizontalAxis, camera->position, camera->position);
    }

    float rotX = 0, rotY = 0;
    if (keyboardctx_isKeyPressed(kb, 'I')) {
        rotY++;
    }
    if (keyboardctx_isKeyPressed(kb, 'K')) {
        rotY--;
    }
    if (keyboardctx_isKeyPressed(kb, 'L')) {
        rotX++;
    }
    if (keyboardctx_isKeyPressed(kb, 'J')) {
        rotX--;
    }

    vec3 axisToRotateY;
    glm_cross(camera->orientation, (vec3){0, 1, 0}, axisToRotateY);
    glm_vec3_rotate(camera->orientation, glm_rad(rotY), axisToRotateY);
    glm_vec3_rotate(camera->orientation, glm_rad(-rotX), (vec3){0, 1, 0});
}

int8_t engine_init(void) {
    if (!glfwInit()) {
        printf("Error initializing GLFW.\nExiting...\n");
        return 0;
    };

    GLFWwindow* window = glfwCreateWindow(WINDOW_MODE_WIDTH, WINDOW_MODE_HEIGHT, "Hello, window! - AMDG", NULL, NULL);

    glfwMakeContextCurrent(window);
    gladLoadGL();

    KeyboardCtx kb = keyboardctx_create();
    keyboardctx_bindwindowctx(&kb, window);

    Mesh square = mesh_init(vertices, indices, sizeof(vertices), sizeof(indices));

    Shader sh = shader_create("./assets/shaders/main.vert", "./assets/shaders/main.frag");
    shader_bind(sh);

    Camera cam = camera_create(WINDOW_MODE_WIDTH / (float)WINDOW_MODE_HEIGHT);
    
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