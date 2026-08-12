// Ad Maiorem Dei Gloriam!

#include "engine.h"

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

    Shader sh = shader_create("./assets/shaders/main.vert", "./assets/shaders/main.frag");
    shader_bind(sh);

    Camera cam = camera_create(WINDOW_MODE_WIDTH / (float)WINDOW_MODE_HEIGHT);

    glActiveTexture(0);
    Texture t = texture_create();
    texture_load_png(t, "assets/textures/atlas.png");

    chunk_init_shaders(sh);

    Chunk chunk = chunk_create();
    float zoffset = 0;
    int zactual = 0;

    chunk_fill_block(&chunk, BLOCK_AIR);

    chunk_set_block(&chunk, 2, (ivec3){0, 0, 0});

    // X ROW - DOTTED
    chunk_set_block(&chunk, BLOCK_DIRT, (ivec3){2, 0, 0});
    chunk_set_block(&chunk, BLOCK_DIRT, (ivec3){4, 0, 0});
    chunk_set_block(&chunk, BLOCK_DIRT, (ivec3){6, 0, 0});
    chunk_set_block(&chunk, BLOCK_DIRT, (ivec3){8, 0, 0});
    chunk_set_block(&chunk, BLOCK_DIRT, (ivec3){10, 0, 0});
    chunk_set_block(&chunk, BLOCK_DIRT, (ivec3){12, 0, 0});
    chunk_set_block(&chunk, BLOCK_DIRT, (ivec3){14, 0, 0});
    // Y ROW - FULL
    chunk_set_block(&chunk, BLOCK_DIRT, (ivec3){0, 1, 0});
    chunk_set_block(&chunk, BLOCK_DIRT, (ivec3){0, 2, 0});
    chunk_set_block(&chunk, BLOCK_DIRT, (ivec3){0, 3, 0});
    chunk_set_block(&chunk, BLOCK_DIRT, (ivec3){0, 4, 0});
    chunk_set_block(&chunk, BLOCK_DIRT, (ivec3){0, 5, 0});
    chunk_set_block(&chunk, BLOCK_DIRT, (ivec3){0, 6, 0});
    chunk_set_block(&chunk, BLOCK_DIRT, (ivec3){0, 7, 0});
    chunk_set_block(&chunk, BLOCK_DIRT, (ivec3){0, 8, 0});
    chunk_set_block(&chunk, BLOCK_DIRT, (ivec3){0, 9, 0});
    chunk_set_block(&chunk, BLOCK_DIRT, (ivec3){0, 10, 0});
    chunk_set_block(&chunk, BLOCK_DIRT, (ivec3){0, 11, 0});
    chunk_set_block(&chunk, BLOCK_DIRT, (ivec3){0, 12, 0});
    chunk_set_block(&chunk, BLOCK_DIRT, (ivec3){0, 13, 0});
    chunk_set_block(&chunk, BLOCK_DIRT, (ivec3){0, 14, 0});
    chunk_set_block(&chunk, BLOCK_DIRT, (ivec3){0, 15, 0});
    // Z ROW - double dashed
    chunk_set_block(&chunk, BLOCK_DIRT, (ivec3){0, 0, 3});
    chunk_set_block(&chunk, BLOCK_DIRT, (ivec3){0, 0, 4});
    chunk_set_block(&chunk, BLOCK_DIRT, (ivec3){0, 0, 7});
    chunk_set_block(&chunk, BLOCK_DIRT, (ivec3){0, 0, 8});
    chunk_set_block(&chunk, BLOCK_DIRT, (ivec3){0, 0, 11});
    chunk_set_block(&chunk, BLOCK_DIRT, (ivec3){0, 0, 12});
    chunk_set_block(&chunk, BLOCK_DIRT, (ivec3){0, 0, 15});
    chunk_build_mesh(&chunk);

    GLint uTex0 = glGetUniformLocation(sh, "tex0");
    glUniform1i(uTex0, 0);

    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(.1f, .2f, .4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        updateCameraInput(&cam, &kb);
        camera_send_matrix(&cam, sh);

        if (keyboardctx_isKeyPressed(&kb, 'V')) zoffset += 0.4f;
        if ((int)zoffset > zactual) {
            zactual = (int)zoffset;
            chunk_set_world_pos(&chunk, (WorldPos){0, 0, zactual});
        }

        texture_bind(t);
        chunk_draw(&chunk);
        glfwSwapBuffers(window);
    }

    shader_destroy(sh);
    chunk_destroy(&chunk);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}