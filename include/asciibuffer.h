// Ad Maiorem Dei Gloriam!
#ifndef ASCIIBUFFER_H
#define ASCIIBUFFER_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define ESCAPE_COLOR_CODE_SIZE 20

struct asciibuffer {
    uint32_t max_size;
    uint32_t wptr;
    uint8_t width; // uint8 should be enough
    uint8_t height;
    char *data;
};

// Returns -1 on errors and 0 on success
int8_t asciibuffer_init(struct asciibuffer *ascbuff, uint8_t width, uint8_t height);

// Prints the whole data array in one syscall. Does NOT include the \n character.
void asciibuffer_print(struct asciibuffer *ascbuff);

// Frees memory and destroys the asciibuffer
void asciibuffer_destroy(struct asciibuffer *ascbuff);

// Sets the next character's background color to the specified rgb value
void asciibuffer_setbgcolor(struct asciibuffer *ascbuff, uint8_t r, uint8_t g, uint8_t b);

// Appends a character to the end of the asciibuffer
void asciibuffer_writechar(struct asciibuffer* ascbuff, char ch);

#endif