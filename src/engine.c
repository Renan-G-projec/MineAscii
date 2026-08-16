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

    engine->player = player_create(&engine->keyboardContext);
    player_set_position(&engine->player, (vec3){5.0f, -50.f, 1.f});

    glActiveTexture(0);
    engine->globalAtlas = texture_create();
    texture_load_png(engine->globalAtlas, "assets/textures/atlas.png");

    engine->world = world_create(193384);
    engine->player.worldContext = &engine->world;

    glEnable(GL_DEPTH_TEST);
    return 0;
}

static void engine_update(Engine *engine) {
    player_update(&engine->player);
}

static void engine_render(Engine *engine) {
    glfwPollEvents();
    glClearColor(.1f, .2f, .4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    world_draw(&engine->world);
    
    player_send_camera_matrix(&engine->player, engine->world.shader);

    texture_bind(engine->globalAtlas);
    glfwSwapBuffers(engine->window);
}

void engine_start_gameloop(Engine *engine) {
    while (!glfwWindowShouldClose(engine->window)) {
        engine_update(engine);
        engine_render(engine);
    }
}

void engine_destroy(Engine *engine) {
    world_destroy(&engine->world);
    player_destroy(&engine->player);
    glfwDestroyWindow(engine->window);
    glfwTerminate();
}
