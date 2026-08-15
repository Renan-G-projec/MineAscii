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
    player_set_position(&player, (vec3){5.0f, -30.f, 1.f});

    glActiveTexture(0);
    Texture t = texture_create();
    texture_load_png(t, "assets/textures/atlas.png");

    chunk_init_shaders(sh);

    World world = world_create(193384);
    player.worldContext = &world;

    GLint uTex0 = glGetUniformLocation(sh, "tex0");
    glUniform1i(uTex0, 0);

    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(.1f, .2f, .4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        world_draw(&world);
        player_update(&player);
        player_send_camera_matrix(&player, sh);

        texture_bind(t);
        glfwSwapBuffers(window);
    }

    world_destroy(&world);
    shader_destroy(sh);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}