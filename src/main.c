// Ad Maiorem Dei Gloriam!
#include <stdio.h>
#include <GLFW/glfw3.h>
#include "asciibuffer.h"

int main() {
    struct asciibuffer ascbuff;
    asciibuffer_init(&ascbuff, 10, 10);
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            asciibuffer_setbgcolor(&ascbuff, 0, 0, x == y ? 255 : 0);
            asciibuffer_writechar(&ascbuff, ' ');
        }
        asciibuffer_writechar(&ascbuff, '\n');
    }

    asciibuffer_print(&ascbuff);
    asciibuffer_destroy(&ascbuff);
    return 0;
}