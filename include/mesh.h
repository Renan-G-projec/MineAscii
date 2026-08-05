// Ad Maiorem Dei Gloriam!
#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include "shader.h"
#include "vbo.h"
#include "vao.h"
#include "ebo.h"

typedef struct {
    GLfloat *vertices;
    GLuint *indices;

    GLint numVertices;
    GLint numIndices;

    VBO vbo;
    VAO vao;
    EBO ebo;
} Mesh;

// Creates a mesh while tracking binds and unbinds
Mesh mesh_init(GLfloat *vertices, GLuint *indices, GLint numVertices, GLint numIndices);

// Helper function that binds the VAO and draws the vertices
void mesh_draw(Mesh);

// Destroys the mesh. WARNING: frees the vertices and indices memory!
void mesh_destroy(Mesh);

#endif