// Ad Maiorem Dei Gloriam!
#include <stdio.h>
#include <GLFW/glfw3.h>
#include "asciibuffer.h"

int main() {
    glfwInitHint(GLFW_VISIBLE, GLFW_TRUE);
    if (!glfwInit()) {
        printf("Error initializing GLFW.\nExiting...\n");
        return 0;
    };

    glfwTerminate();
    return 0;
}