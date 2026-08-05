// Ad Maiorem Dei Gloriam!
#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <stdlib.h>
#include "shader.h"
#include "vbo.h"
#include "vao.h"
#include "ebo.h"

typedef struct {
    GLfloat *vertices;
    GLuint *indices;

    GLsizei numVertices;
    GLsizei numIndices;

    VBO vbo;
    VAO vao;
    EBO ebo;
} Mesh;

// Creates a mesh while tracking binds and unbinds
Mesh mesh_init(GLfloat *vertices, GLuint *indices, GLsizei numVertices, GLsizei numIndices);

// Helper function that binds the VAO and draws the vertices
void mesh_draw(Mesh *);

// Destroys the mesh. WARNING: Does not frees any memory into the Vertices or indices pointer!
void mesh_destroy(Mesh *);

#endif