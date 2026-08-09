// Ad Maiorem Dei Gloriam!
#include "graphics/ebo.h"

EBO ebo_create(void) {
    EBO ebo;
    glGenBuffers(1, &ebo);
    return ebo;
}

void ebo_send_data(EBO ebo, GLsizei size, GLint *data) {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void ebo_bind(EBO e) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e);
}

void ebo_unbind(void) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ebo_destroy(EBO e) {
    glDeleteBuffers(1, &e);
}