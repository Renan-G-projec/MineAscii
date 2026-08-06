// Ad Maiorem Dei Gloriam!
#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>
#include <string.h>

#include <GLFW/glfw3.h>

// About this file
// I made this file to provide an wrapper to input handling, as the
// game will be developen in a window framebuffer but the final will be
// an offscreen buffer and therefore will have different input handlings

typedef struct  {
    uint8_t keyState[256];
    GLFWwindow* windowCtx; // Used during development in screen
} KeyboardCtx;

KeyboardCtx keyboardctx_create(void);

// Used for capturing input while in the screen dev mode
void keyboardctx_bindwindowctx(KeyboardCtx *, GLFWwindow *windowPtr);

void keyboardctx_update(KeyboardCtx *);

// Returns 0 on false and 1 on true
uint8_t keyboardctx_isKeyPressed(KeyboardCtx *, unsigned char key);

#endif