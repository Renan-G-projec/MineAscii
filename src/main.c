// Ad Maiorem Dei Gloriam!
#include <stdio.h>
#include "framebuffer.h"

int main() {
    struct framebuffer fb;
    framebuffer_init(&fb, 10, 10);
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            framebuffer_setbgcolor(&fb, 0, 0, x == y ? 255 : 0);
            framebuffer_writechar(&fb, ' ');
        }
        framebuffer_writechar(&fb, '\n');
    }

    framebuffer_print(&fb);
    framebuffer_destroy(&fb);
    return 0;
}