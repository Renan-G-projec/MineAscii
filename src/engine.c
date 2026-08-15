// Ad Maiorem Dei Gloriam!

#include "engine.h"

int8_t engine_init(Engine *engine) {
    if (!glfwInit()) {
        printf("Error initializing GLFW.\nExiting...\n");
        return -1;
    };

    engine->window = glfwCreateWindow(WINDOW_MODE_WIDTH, WINDOW_MODE_HEIGHT, "Hello, window! - AMDG", NULL, NULL);

    glfwMakeContextCurrent(engine->window);
    gladLoadGL();

    engine->keyboardContext = keyboardctx_create();
    keyboardctx_bindwindowctx(&engine->keyboardContext, engine->window);

    Shader sh = shader_create("./assets/shaders/main.vert", "./assets/shaders/main.frag");
    shader_bind(sh);

    engine->player = player_create(&engine->keyboardContext);
    player_set_position(&engine->player, (vec3){5.0f, -50.f, 1.f});

    glActiveTexture(0);
    Texture t = texture_create();
    texture_load_png(t, "assets/textures/atlas.png");

    chunk_init_shaders(sh);

    engine->world = world_create(193384);
    engine->player.worldContext = &engine->world;

    GLint uTex0 = glGetUniformLocation(sh, "tex0");
    glUniform1i(uTex0, 0);

    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(engine->window)) {
        glfwPollEvents();
        glClearColor(.1f, .2f, .4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        world_draw(&engine->world);
        player_update(&engine->player);
        player_send_camera_matrix(&engine->player, sh);

        texture_bind(t);
        glfwSwapBuffers(engine->window);
    }

    world_destroy(&engine->world);
    shader_destroy(sh);
    glfwDestroyWindow(engine->window);
    glfwTerminate();
    return 0;
}