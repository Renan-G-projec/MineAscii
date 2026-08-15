// Ad Maiorem Dei Gloriam!
#ifndef ENGINE_H
#define ENGINE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <math.h>
#include "core/player.h"
#include "core/chunk.h"
#include "core/player.h"
#include "core/world.h"
#include "graphics/texture.h"
#include "graphics/camera.h"
#include "graphics/input.h"
#include "graphics/shader.h"
#include "graphics/mesh.h"

typedef struct {
    GLFWwindow *window;
    KeyboardCtx keyboardContext;

    Texture globalAtlas;
    World world;
    Player player;

    Shader tempShader; // Shall be of the world
} Engine;

int8_t engine_init(Engine *);
void engine_start_gameloop(Engine *);
void engine_destroy(Engine *);

#endif