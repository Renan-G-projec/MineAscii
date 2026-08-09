// Ad Maiorem Dei Gloriam!
#ifndef ENGINE_H
#define ENGINE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <math.h>
#include "graphics/texture.h"
#include "graphics/camera.h"
#include "graphics/input.h"
#include "graphics/shader.h"
#include "graphics/mesh.h"

#define WINDOW_MODE_WIDTH 1280
#define WINDOW_MODE_HEIGHT 720

// Initializes the engine. If fails, returns -1. Runs all the game until finish.
int8_t engine_init(void);

#endif