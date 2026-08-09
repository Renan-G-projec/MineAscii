// Ad Maiorem Dei Gloriam!
#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdint.h>
#include <glad/glad.h>
#include <stb_image.h>

typedef GLuint Texture;

// Initializes the texture
Texture texture_create(void);

// Loads from a file with stb image
void texture_load_png(Texture, const char *filename);

// Binds the texture
void texture_bind(Texture);

void texture_unbind(void);

// Destroys the texture and frees from vram
void texture_destroy(Texture);

#endif