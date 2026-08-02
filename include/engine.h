// Ad Maiorem Dei Gloriam!
#ifndef ENGINE_H
#define ENGINE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "vao.h"
#include "vbo.h"

// Initializes the engine. If fails, returns -1. Runs all the game until finish.
int8_t engine_init();

#endif