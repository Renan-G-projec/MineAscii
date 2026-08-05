// Ad Maiorem Dei Gloriam!
#include "vao.h"

VAO vao_create(void) {
    VAO vao;
    glGenVertexArrays(1, &vao);

    return vao;
}

void vao_bind(VAO v) {
    glBindVertexArray(v);
}

void vao_unbind(void) {
    glBindVertexArray(0);
}

void vao_define(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid *offset) {
    glVertexAttribPointer(index, size, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(index);
}

void vao_destroy(VAO v) {
    glDeleteVertexArrays(1, &v);
}
