// Ad Maiorem Dei Gloriam!
#ifndef SHADER_H
#define SHADER_H

#include <stdint.h>

typedef unsigned int Shader;

// Returns the Shader struct and links it
Shader shader_create(const char *vertexShaderPath, const char *fragmentShaderPath);

// Binds the shader
void shader_bind(Shader shader);

// Deletes the shader
void shader_destroy(Shader shader);

#endif