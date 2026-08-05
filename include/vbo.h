// Ad Maiorem Dei Gloriam!
#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>

typedef GLuint VBO;

// Initializes the VBO buffer
VBO vbo_create(void);

// Copies the data to VBO
void vbo_set_data(VBO, GLuint size, GLfloat *data);

void vbo_bind(VBO);
void vbo_unbind(void);

void vbo_destroy(VBO);

#endif