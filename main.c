// Ad Maiorem Dei Gloriam!
#include <stdio.h>
#include <stdint.h>
#include <malloc.h>

#include <unistd.h>
#include <memory.h>

#define ESCAPE_COLOR_CODE_SIZE 22

struct framebuffer {
    uint32_t max_size;
    uint32_t current_size;
    uint32_t wptr;
    uint8_t width; // uint8 should be enough
    uint8_t height;
    char *data;
};

// Returns -1 on errors and 0 on success
int8_t framebuffer_init(struct framebuffer *fb, uint8_t width, uint8_t height) {
    fb->max_size = ESCAPE_COLOR_CODE_SIZE * width * height + height; // height again because of the newlines
    fb->current_size = width * height;
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
    write(STDOUT_FILENO, fb->data, fb->current_size);
}

void framebuffer_destroy(struct framebuffer *fb) {
    free(fb->data);
}

void framebuffer_setbgcolor(struct framebuffer *fb, uint8_t r, uint8_t g, uint8_t b) {
    snprintf(fb->data + fb->wptr, ESCAPE_COLOR_CODE_SIZE, "\033[48;2;%03d;%03d;%03dm", r, g, b);
    fb->wptr += ESCAPE_COLOR_CODE_SIZE;
    fb->current_size += ESCAPE_COLOR_CODE_SIZE;
}

static inline void framebuffer_writechar(struct framebuffer* fb, char ch) {
    fb->current_size++;
    fb->data[fb->wptr++] = ch;
}

int main() {
    struct framebuffer fb;
    framebuffer_init(&fb, 10, 10);
    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            framebuffer_setbgcolor(&fb, 0, 0, x == y ? 255 : 0);
            framebuffer_writechar(&fb, ' ');
        }
        framebuffer_writechar(&fb, '\n');
    }

    framebuffer_print(&fb);
    framebuffer_destroy(&fb);
    return 0;
}