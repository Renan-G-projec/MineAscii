// Ad Maiorem Dei Gloriam!
#include "graphics/mesh.h"

Mesh mesh_init(GLfloat *vertices, GLuint *indices, GLsizei numVertices, GLsizei numIndices) {
    Mesh mesh;

    mesh.vertices = vertices;
    mesh.indices = indices;

    mesh.numVertices = numVertices;
    mesh.numIndices = numIndices;

    mesh.vao = vao_create();
    vao_bind(mesh.vao);

    mesh.vbo = vbo_create();
    vbo_bind(mesh.vbo);
    vbo_set_data(mesh.vbo, numVertices, vertices);

    mesh.ebo = ebo_create();
    ebo_bind(mesh.ebo);
    ebo_send_data(mesh.ebo, numIndices, indices);

    vao_define(0, 3, GL_FLOAT, 5 * sizeof(GLfloat), (void *)0); // Coords
    vao_define(1, 2, GL_FLOAT, 5 * sizeof(GLfloat), (void *)(3 * sizeof(GL_FLOAT))); // UV

    // Unbinds for security
    // Due to only unbinding on constructor shall not have any reasonable impact on performance
    vao_unbind();
    ebo_unbind();
    vbo_unbind();

    return mesh;
}

void mesh_draw(Mesh *mesh) {
    vao_bind(mesh->vao);
    glDrawElements(GL_TRIANGLES, mesh->numIndices, GL_UNSIGNED_INT, NULL);
}

void mesh_destroy(Mesh *mesh) {
    vao_destroy(mesh->vao);
    ebo_destroy(mesh->ebo);
    vbo_destroy(mesh->vbo);
}