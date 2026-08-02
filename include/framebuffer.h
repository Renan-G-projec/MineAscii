// Ad Maiorem Dei Gloriam!
#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define ESCAPE_COLOR_CODE_SIZE 20

struct framebuffer {
    uint32_t max_size;
    uint32_t wptr;
    uint8_t width; // uint8 should be enough
    uint8_t height;
    char *data;
};

// Returns -1 on errors and 0 on success
int8_t framebuffer_init(struct framebuffer *fb, uint8_t width, uint8_t height);

// Prints the whole data array in one syscall. Does NOT include the \n character.
void framebuffer_print(struct framebuffer *fb);

// Frees memory and destroys the framebuffer
void framebuffer_destroy(struct framebuffer *fb);

// Sets the next character's background color to the specified rgb value
void framebuffer_setbgcolor(struct framebuffer *fb, uint8_t r, uint8_t g, uint8_t b);

// Appends a character to the end of the framebuffer
void framebuffer_writechar(struct framebuffer* fb, char ch);

#endif