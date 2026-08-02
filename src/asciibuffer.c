// Ad Maiorem Dei Gloriam!
#include "asciibuffer.h"

// About this file
// So the asciibuffer responsability is to handle and print ascii characters onto the screen.
// It is asciiwork-agnostic but a little heavy in the worst case scenario (all the characters being a different color)

// IT DOES NOT OPTIMIZE THE BACKGROUND COMPRESSING

// Returns -1 on errors and 0 on success
int8_t asciibuffer_init(struct asciibuffer *asciibuff, uint8_t width, uint8_t height) {
    asciibuff->max_size = ESCAPE_COLOR_CODE_SIZE * width * height + height; // height again because of the newlines
    asciibuff->wptr = 0;
    asciibuff->width = width;
    asciibuff->height = height;
    asciibuff->data = malloc(asciibuff->max_size);

    if (!asciibuff->data) {
        return -1;
    }
    return 0;
}

void asciibuffer_print(struct asciibuffer *asciibuff) {
    write(STDOUT_FILENO, asciibuff->data, asciibuff->wptr);
}

void asciibuffer_destroy(struct asciibuffer *asciibuff) {
    free(asciibuff->data);
    // Resets the terminal background color
    write(STDOUT_FILENO, "\033[0m", 4);
}

void asciibuffer_setbgcolor(struct asciibuffer *asciibuff, uint8_t r, uint8_t g, uint8_t b) {
    int written = snprintf(asciibuff->data + asciibuff->wptr, ESCAPE_COLOR_CODE_SIZE, "\033[48;2;%d;%d;%dm", r, g, b);
    asciibuff->wptr += written;
}

void asciibuffer_writechar(struct asciibuffer* asciibuff, char ch) {
    asciibuff->data[asciibuff->wptr++] = ch;
}