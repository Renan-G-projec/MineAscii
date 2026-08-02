// Ad Maiorem Dei Gloriam!
#include "framebuffer.h"

// About this file
// So the framebuffer responsability is to handle and print ascii characters onto the screen.
// It is framework-agnostic but a little heavy in the worst case scenario (all the characters being a different color)

// Returns -1 on errors and 0 on success
int8_t framebuffer_init(struct framebuffer *fb, uint8_t width, uint8_t height) {
    fb->max_size = ESCAPE_COLOR_CODE_SIZE * width * height + height; // height again because of the newlines
    fb->wptr = 0;
    fb->width = width;
    fb->height = height;
    fb->data = malloc(fb->max_size);

    if (!fb->data) {
        return -1;
    }
    return 0;
}

void framebuffer_print(struct framebuffer *fb) {
    write(STDOUT_FILENO, fb->data, fb->wptr);
}

void framebuffer_destroy(struct framebuffer *fb) {
    free(fb->data);
    // Resets the terminal background color
    write(STDOUT_FILENO, "\033[0m", 4);
}

void framebuffer_setbgcolor(struct framebuffer *fb, uint8_t r, uint8_t g, uint8_t b) {
    int written = snprintf(fb->data + fb->wptr, ESCAPE_COLOR_CODE_SIZE, "\033[48;2;%d;%d;%dm", r, g, b);
    fb->wptr += written;
}

void framebuffer_writechar(struct framebuffer* fb, char ch) {
    fb->data[fb->wptr++] = ch;
}