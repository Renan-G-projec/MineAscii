// Ad Maiorem Dei Gloriam!
#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>

typedef GLuint EBO;

// Creates an element buffer
EBO ebo_create(void);

// Copies the EBO vertices
void ebo_send_data(EBO, GLsizei size, GLint *data);

// Binds the EBO
void ebo_bind(EBO);

// Unbinds it
void ebo_unbind(void);

// Destroys and frees the memory of the element buffer
void ebo_destroy(EBO);

#endif