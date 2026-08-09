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


    int imgWidth, imgHeight, numColorChannels;
    stbi_set_flip_vertically_on_load(1);
    unsigned char *bytes = stbi_load("assets/textures/atlas.png", &imgWidth, &imgHeight, &numColorChannels, 0);
    
    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    stbi_image_free(bytes);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glGenerateMipmap(GL_TEXTURE_2D);

    GLint uTex0 = glGetUniformLocation(sh, "tex0");
    glUniform1i(uTex0, 0);

    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        updateCameraInput(&cam, &kb);
        camera_send_matrix(&cam, sh);

        glBindTexture(GL_TEXTURE_2D, texture);
        mesh_draw(&square);
        glfwSwapBuffers(window);
    }

    shader_destroy(sh);
    mesh_destroy(&square);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}