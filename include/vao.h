// Ad Maiorem Dei Gloriam!
#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>

typedef GLuint VAO;

// Creates an Vertex Array Object
VAO vao_create();

// Defines the attribute of an vertex
void vao_define(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid* offset);

// Binds the Vertex Array Object
void vao_bind(VAO);

// Unbinds the Vertex Array Object
void vao_unbind();

// Deletes the Vertex Array Object
void vao_destroy(VAO);

#endif