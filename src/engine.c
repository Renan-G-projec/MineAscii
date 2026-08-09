// Ad Maiorem Dei Gloriam!

#include "engine.h"

float vertices[] = {
    // FRONT
    -1.0f, -1.0f, -1.0f, 0.0f, 0.0625f * 5.0f, // Front down left
    -1.0f, 1.0f, -1.0f, 0.0f, 0.0625f * 6.0f, // Front up left
    1.0f, -1.0f, -1.0f, 0.03125f, 0.0625f * 5.0f, // Front down right
    1.0f, 1.0f, -1.0f, 0.03125f, 0.0625f * 6.0f, // Front up right

    // BACK
    -1.0f, -1.0f, 1.0f, 0.0f, 0.0625f * 5.0f, // Back down left
    -1.0f, 1.0f, 1.0f, 0.0f, 0.0625f * 6.0f, // Back up left
    1.0f, -1.0f, 1.0f, 0.03125f, 0.0625f * 5.0f, // Back down right
    1.0f, 1.0f, 1.0f, 0.03125f, 0.0625f * 6.0f, // Back up right
    
    // LEFT
    -1.0f, -1.0f, 1.0f, 0.0f, 0.0625f * 5.0f, // Left down left
    -1.0f, 1.0f, 1.0f, 0.0f, 0.0625f * 6.0f, // Left up left
    -1.0f, -1.0f, -1.0f, 0.03125f, 0.0625f * 5.0f, // Left down right
    -1.0f, 1.0f, -1.0f, 0.03125f, 0.0625f * 6.0f, // Left up right

    // RIGHT
    1.0f, -1.0f, -1.0f, 0.0f, 0.0625f * 5.0f, // Right down left
    1.0f, 1.0f, -1.0f, 0.0f, 0.0625f * 6.0f, // Right up left
    1.0f, -1.0f, 1.0f, 0.03125f, 0.0625f * 5.0f, // Right down right
    1.0f, 1.0f, 1.0f, 0.03125f, 0.0625f * 6.0f, // Right up right

    // TOP
    -1.0f, 1.0f, -1.0f, 0.03125f * 3.0f, 0.0625f * 5.0f, // Top down left
    -1.0f, 1.0f, 1.0f, 0.03125f * 3.0f, 0.0625f * 6.0f, // Top up left
    1.0f, 1.0f, -1.0f, 0.03125f * 4.0f, 0.0625f * 5.0f, // Top down right
    1.0f, 1.0f, 1.0f, 0.03125f * 4.0f, 0.0625f * 6.0f, // Top up right

    // DOWN
    -1.0f, -1.0f, 1.0f, 0.03125f * 8.0f, 0.0625f * 11.0f, // Down down left
    -1.0f, -1.0f, -1.0f, 0.03125f * 8.0f, 0.0625f * 12.0f, // Down up left
    1.0f, -1.0f, 1.0f, 0.03125f * 9.0f, 0.0625f * 11.0f, // Down down right
    1.0f, -1.0f, -1.0f, 0.03125f * 9.0f, 0.0625f * 12.0f, // Down up right
};

unsigned int indices[] = {  // note that we start from 0!
    // FRONT
    0, 1, 2,
    1, 3, 2,

    // BACK
    4, 5, 6,
    5, 7, 6,

    // LEFT
    8, 9, 10,
    9, 11, 10,

    // RIGHT
    12, 13, 14,
    13, 15, 14,

    // TOP
    16, 17, 18,
    17, 19, 18,

    // DOWN
    20, 21, 22,
    21, 23, 22
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
        rotY += 10;
    }
    if (keyboardctx_isKeyPressed(kb, 'K')) {
        rotY -= 10;
    }
    if (keyboardctx_isKeyPressed(kb, 'L')) {
        rotX += 10;
    }
    if (keyboardctx_isKeyPressed(kb, 'J')) {
        rotX -= 10;
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

    glActiveTexture(0);
    Texture t = texture_create();
    texture_load_png(t, "assets/textures/atlas.png");

    GLint uTex0 = glGetUniformLocation(sh, "tex0");
    glUniform1i(uTex0, 0);

    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(.1f, .2f, .4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        updateCameraInput(&cam, &kb);
        camera_send_matrix(&cam, sh);

        texture_bind(t);
        mesh_draw(&square);
        glfwSwapBuffers(window);
    }

    shader_destroy(sh);
    mesh_destroy(&square);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}