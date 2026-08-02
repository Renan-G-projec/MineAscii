// Ad Maiorem Dei Gloriam!
#ifndef ENGINE_H
#define ENGINE_H

#include <GLFW/glfw3.h>
#include "shader.h"

// Holds all the game together
struct Engine {
    GLFWwindow* window;   
};

// Initializes the engine. If fails, returns -1. Runs all the game until finish.
int8_t engine_init();

#endif