// Ad Maiorem Dei Gloriam!
#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graphics/shader.h"
#include "graphics/vbo.h"
#include "graphics/vao.h"
#include "graphics/ebo.h"

typedef struct {
    GLsizei numVertices;
    GLsizei numIndices;

    VBO vbo;
    VAO vao;
    EBO ebo;

    bool loadedData;
} Mesh;

// Creates a mesh while tracking binds and unbinds
Mesh mesh_init(GLfloat *vertices, GLuint *indices, GLsizei numVertices, GLsizei numIndices);

// Helper function that binds the VAO and draws the vertices
void mesh_draw(Mesh *);

// Changes the vertices and indices
void mesh_update(Mesh *, GLfloat *vertices, GLuint *indices, GLsizei numVertices, GLsizei numIndices);

// Destroys the mesh. WARNING: Does not frees any memory into the Vertices or indices pointer!
void mesh_destroy(Mesh *);

#endif