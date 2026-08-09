// Ad Maiorem Dei Gloriam!
#include "graphics/input.h"

KeyboardCtx keyboardctx_create(void) {
    KeyboardCtx kb;
    memset(kb.keyState, 0, 256);
    kb.windowCtx = NULL;
    return kb;
}

void keyboardctx_update(KeyboardCtx *kb) {
    // When using termios, this will implement something with kbhit
    return;
}

void keyboardctx_bindwindowctx(KeyboardCtx* kb, GLFWwindow *win) {
    kb->windowCtx = win;
    return;
}

uint8_t keyboardctx_isKeyPressed(KeyboardCtx *kb, unsigned char key) {
    return glfwGetKey(kb->windowCtx, key);
}