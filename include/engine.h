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
#include "graphics/asciibuffer.h"
#include "graphics/texture.h"
#include "graphics/camera.h"
#include "graphics/input.h"
#include "graphics/shader.h"
#include "graphics/mesh.h"

#define SKY_COLOR (113/255.0f), (185/255.0f), (255/255.0f), (1.0f)

typedef struct {
    GLFWwindow *window;
    KeyboardCtx keyboardContext;
    struct asciibuffer screen;

    Texture globalAtlas;
    World world;
    Player player;
} Engine;

int8_t engine_init(Engine *);
void engine_start_gameloop(Engine *);
void engine_destroy(Engine *);

#endif