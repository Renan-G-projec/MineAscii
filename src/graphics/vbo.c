// Ad Maiorem Dei Gloriam!
#include "graphics/vbo.h"

VBO vbo_create(void) {
    VBO v;
    glGenBuffers(1, &v);
    
    return v;
}

void vbo_set_data(VBO v, GLuint size, GLfloat *d) {
    glBufferData(GL_ARRAY_BUFFER, size, d, GL_STATIC_DRAW);
}

void vbo_bind(VBO v) {
    glBindBuffer(GL_ARRAY_BUFFER, v);
}

void vbo_unbind(void) {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void vbo_destroy(VBO v) {
    glDeleteBuffers(1, &v);
}