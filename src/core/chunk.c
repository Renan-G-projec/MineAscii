// Ad Maiorem Dei Gloriam!
#include "core/chunk.h"

// Helper function
// Pushes to the array and changes the icon
static void add_vertex(GLfloat *vertices, int *index, GLfloat x, GLfloat y, GLfloat z, GLfloat u, GLfloat v) {
    vertices[(*index)++] = x;
    vertices[(*index)++] = y;
    vertices[(*index)++] = z;
    vertices[(*index)++] = u;
    vertices[(*index)++] = v;
}

// Takes the indices array and populates 6 indices
static void add_square_indices(GLuint *indices, unsigned int *index) {
    int verticesOffset = (*index) / 6 * 4;

    // First triangle
    indices[(*index)++] = verticesOffset;
    indices[(*index)++] = verticesOffset + 1;
    indices[(*index)++] = verticesOffset + 2;

    // Second Triangle
    indices[(*index)++] = verticesOffset + 2;
    indices[(*index)++] = verticesOffset + 3;
    indices[(*index)++] = verticesOffset;
}

// Adds and populates 4 vertices and 6 indices to make a cube face.
static void add_cube_face(Block block, CubeFace faceDirection, GLfloat *vertices, GLuint *indices, int *verticesIndex, unsigned int *indicesIndex, int x, int y, int z) {
    UV bottom_left = block_get_uv(block, faceDirection, BOTTOM_LEFT);
    UV top_left = block_get_uv(block, faceDirection, TOP_LEFT);
    UV bottom_right = block_get_uv(block, faceDirection, BOTTOM_RIGHT);
    UV top_right = block_get_uv(block, faceDirection, TOP_RIGHT);

    float realX, realY, realZ;

    // Really bad code LOL. Author: myself
    switch (faceDirection) {
        case FRONT: 
            add_vertex(vertices, verticesIndex, x, y, z, bottom_left.u, bottom_left.v);
            add_vertex(vertices, verticesIndex, x, y + 1, z, top_left.u, top_left.v);
            add_vertex(vertices, verticesIndex, x + 1, y + 1, z, top_right.u, top_right.v);
            add_vertex(vertices, verticesIndex, x + 1, y, z, bottom_right.u, bottom_right.v);
            break;
        case BACK: 
            add_vertex(vertices, verticesIndex, x, y, z + 1, bottom_left.u, bottom_left.v);
            add_vertex(vertices, verticesIndex, x, y + 1, z + 1, top_left.u, top_left.v);
            add_vertex(vertices, verticesIndex, x + 1, y + 1, z + 1, top_right.u, top_right.v);
            add_vertex(vertices, verticesIndex, x + 1, y, z + 1, bottom_right.u, bottom_right.v);
            break;
        case TOP:
            add_vertex(vertices, verticesIndex, x, y + 1, z, bottom_left.u, bottom_left.v);
            add_vertex(vertices, verticesIndex, x, y + 1, z + 1, top_left.u, top_left.v);
            add_vertex(vertices, verticesIndex, x + 1, y + 1, z + 1, top_right.u, top_right.v);
            add_vertex(vertices, verticesIndex, x + 1, y + 1, z, bottom_right.u, bottom_right.v);
            break;
        case BOTTOM:
            add_vertex(vertices, verticesIndex, x, y, z, bottom_left.u, bottom_left.v);
            add_vertex(vertices, verticesIndex, x, y, z + 1, top_left.u, top_left.v);
            add_vertex(vertices, verticesIndex, x + 1, y, z + 1, top_right.u, top_right.v);
            add_vertex(vertices, verticesIndex, x + 1, y, z, bottom_right.u, bottom_right.v);
            break;
        case LEFT:
            add_vertex(vertices, verticesIndex, x, y, z + 1, bottom_left.u, bottom_left.v);
            add_vertex(vertices, verticesIndex, x, y + 1, z + 1, top_left.u, top_left.v);
            add_vertex(vertices, verticesIndex, x, y + 1, z, top_right.u, top_right.v);
            add_vertex(vertices, verticesIndex, x, y, z, bottom_right.u, bottom_right.v);
            break;
        case RIGHT:
            add_vertex(vertices, verticesIndex, x + 1, y, z + 1, bottom_left.u, bottom_left.v);
            add_vertex(vertices, verticesIndex, x + 1, y + 1, z + 1, top_left.u, top_left.v);
            add_vertex(vertices, verticesIndex, x + 1, y + 1, z, top_right.u, top_right.v);
            add_vertex(vertices, verticesIndex, x + 1, y, z, bottom_right.u, bottom_right.v);
            break;
    }
    
    add_square_indices(indices, indicesIndex);
}

Chunk chunk_create(void) {
    Chunk chunk;

    chunk.blocks = malloc(CHUNK_WIDTH * CHUNK_DEPTH * CHUNK_HEIGHT * sizeof(Block));
    if (!chunk.blocks) {
        printf("Error: Could not create chunk, not enough memory.\n");
        exit(-1);
    }

    // Default worldPos
    chunk.worldPos = (WorldPos){0, 0, 0};
    glm_mat4_identity(chunk.modelMat);

    // Not built yet
    chunk.mesh = mesh_init(NULL, NULL, 0, 0);

    return chunk;
}

void chunk_build_mesh(Chunk *chunk) {
    GLfloat *vertices = malloc(sizeof(GLfloat) * 120 * CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_DEPTH);
    GLuint *indices = malloc(sizeof(GLuint) * 36 * CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_DEPTH);

    unsigned int currentVertexIndex = 0;
    unsigned int currentIndiceIndex = 0;

    for (int x = 0; x < CHUNK_WIDTH; ++x) {
        for (int y = 0; y < CHUNK_HEIGHT; ++y) {
            for (uint8_t z = 0; z < CHUNK_DEPTH; ++z) {
                Block block = chunk_get_block(chunk, (ivec3){x, y, z});
                if (block != BLOCK_AIR) {
                    if (chunk_get_block(chunk, (ivec3){x, y + 1, z}) == BLOCK_AIR) add_cube_face(block, TOP, vertices, indices, &currentVertexIndex, &currentIndiceIndex, x, y, z);
                    if (chunk_get_block(chunk, (ivec3){x, y - 1, z}) == BLOCK_AIR) add_cube_face(block, BOTTOM, vertices, indices, &currentVertexIndex, &currentIndiceIndex, x, y, z);
                    if (chunk_get_block(chunk, (ivec3){x - 1, y, z}) == BLOCK_AIR) add_cube_face(block, LEFT, vertices, indices, &currentVertexIndex, &currentIndiceIndex, x, y, z);
                    if (chunk_get_block(chunk, (ivec3){x + 1, y, z}) == BLOCK_AIR) add_cube_face(block, RIGHT, vertices, indices, &currentVertexIndex, &currentIndiceIndex, x, y, z);
                    if (chunk_get_block(chunk, (ivec3){x, y, z - 1}) == BLOCK_AIR) add_cube_face(block, FRONT, vertices, indices, &currentVertexIndex, &currentIndiceIndex, x, y, z);
                    if (chunk_get_block(chunk, (ivec3){x, y, z + 1}) == BLOCK_AIR) add_cube_face(block, BACK, vertices, indices, &currentVertexIndex, &currentIndiceIndex, x, y, z);
                }
            }
        }
    }

    mesh_update(&chunk->mesh, vertices, indices, currentVertexIndex, currentIndiceIndex);
    free(vertices);
    free(indices);
}

void chunk_draw(Chunk *chunk, GLuint modelUniformLocation) {
    glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, chunk->modelMat[0]);
    mesh_draw(&chunk->mesh);
}

void chunk_destroy(Chunk *chunk) {
    mesh_destroy(&chunk->mesh);

    if (chunk->blocks) {
        free(chunk->blocks);
    }
}

// Helper functions
void chunk_set_block(Chunk *chunk, Block block, ivec3 pos) {
    int x = pos[0];
    int y = pos[1];
    int z = pos[2];

    if (x < 0 || x >= CHUNK_WIDTH) return;
    if (y < 0 || y >= CHUNK_HEIGHT) return;
    if (z < 0 || z >= CHUNK_DEPTH) return;

    int index = x * CHUNK_DEPTH * CHUNK_HEIGHT + y * CHUNK_DEPTH + z;
    chunk->blocks[index] = block;
}

Block chunk_get_block(Chunk *chunk, ivec3 pos) {
    int x = pos[0];
    int y = pos[1];
    int z = pos[2];

    if (x < 0 || x >= CHUNK_WIDTH) return BLOCK_AIR;
    if (y < 0 || y >= CHUNK_HEIGHT) return BLOCK_AIR;
    if (z < 0 || z >= CHUNK_DEPTH) return BLOCK_AIR;

    int index = x * CHUNK_DEPTH * CHUNK_HEIGHT + y * CHUNK_DEPTH + z;
    return chunk->blocks[index];
}

// Probably this will copy
// Hope it not copies any random pointer
inline void chunk_set_world_pos(Chunk *chunk, WorldPos pos) {
    chunk->worldPos = pos;
    glm_mat4_identity(chunk->modelMat);
    glm_translate(chunk->modelMat, (vec3){pos.x * CHUNK_WIDTH, pos.y * CHUNK_HEIGHT, pos.z * CHUNK_DEPTH});
}

inline WorldPos chunk_get_world_pos(Chunk *chunk) {
    return chunk->worldPos;
}

void chunk_generate(Chunk* chunk, int seed) {
    chunk_fill_block(chunk, 0);
    
    // Generating the heightmap here because in the blockfill loop it would cause a lot of cache misses.
    uint16_t heightMap[CHUNK_WIDTH * CHUNK_DEPTH];
    for (int x = 0; x < CHUNK_WIDTH; ++x) {
        for (int z = 0; z < CHUNK_DEPTH; ++z) {
            float raw = pnoise2d((chunk->worldPos.x * CHUNK_WIDTH + x) * 0.01, (chunk->worldPos.z * CHUNK_DEPTH + z) * 0.01, 4, 1, seed);
            heightMap[x * CHUNK_DEPTH + z] = CHUNK_BASE + (raw * (CHUNK_HEIGHT - CHUNK_BASE));
        }
    }
    
    for (int x = 0; x < CHUNK_WIDTH; ++x) {
        for (int y = 0; y < CHUNK_HEIGHT; ++y) {
            for (int z = 0; z < CHUNK_DEPTH; ++z) {
                if (y <= heightMap[x * CHUNK_DEPTH + z]) {
                    Block block = BLOCK_STONE;
                    if ((heightMap[x * CHUNK_DEPTH + z] - y) < 3) block = BLOCK_DIRT;
                    if ((heightMap[x * CHUNK_DEPTH + z] - y) < 1) block = BLOCK_GRASS;
                    chunk_set_block(chunk, block, (ivec3){x, y, z});
                }
            }
        }
    }
}

// Remove this in release probably
void chunk_fill_block(Chunk *chunk, Block desiredBlock) {
    // Don't know if uint8_t is premature optimization POV: It was LOL
    // But shall fit well
    for (int x = 0; x < CHUNK_WIDTH; ++x) {
        for (int y = 0; y < CHUNK_HEIGHT; ++y) {
            for (int z = 0; z < CHUNK_DEPTH; ++z) {
                chunk_set_block(chunk, desiredBlock, (ivec3){x, y, z});
            }
        }
    }
}