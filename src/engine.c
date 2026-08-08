// Ad Maiorem Dei Gloriam!

#include "engine.h"

float vertices[] = {
    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, // front down-left
    -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, // front up-left
    1.0f, -1.0f, -1.0f, 1.0f, 0.0f, // front down-right
    1.0f, 1.0f, -1.0f, 1.0f, 1.0f, // front up-right
    -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, // back down-left
    -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // back up-left
    1.0f, -1.0f, 1.0f, 1.0f, 0.0f, // back down-right
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // back up-right
};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 2, // front face
    1, 3, 2, // front face
    0, 1, 4, // Left face
    4, 5, 1, // Left face 
    1, 5, 7, // top face
    7, 3, 1, // top face
    0, 4, 2, // bottom face
    4, 6, 2, // Bottom face 
    2, 3, 6, // Right face
    6, 7, 3, // Right face
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


    int imgWidth, imgHeight, numColorChannels;
    stbi_set_flip_vertically_on_load(1);
    unsigned char *bytes = stbi_load("assets/textures/grass_block_side.png", &imgWidth, &imgHeight, &numColorChannels, 0);
    
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