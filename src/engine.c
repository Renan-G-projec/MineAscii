// Ad Maiorem Dei Gloriam!

#include "engine.h"

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

    Player player = player_create(&kb);

    glActiveTexture(0);
    Texture t = texture_create();
    texture_load_png(t, "assets/textures/atlas.png");

    chunk_init_shaders(sh);

    Chunk chunk = chunk_create();
    float zoffset = 0;
    int zactual = 0;

    chunk_generate(&chunk, 1);
    chunk_build_mesh(&chunk);

    GLint uTex0 = glGetUniformLocation(sh, "tex0");
    glUniform1i(uTex0, 0);

    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(.1f, .2f, .4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        player_update(&player);
        player_send_camera_matrix(&player, sh);

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