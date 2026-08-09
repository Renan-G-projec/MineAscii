// Ad Maiorem Dei Gloriam!
#include "core/chunk.h"

float dirtVertices[] = {
    // FRONT (Z = 0)
    0.0f, 0.0f, 0.0f,  0.0f,     0.0625f * 5.0f,
    1.0f, 0.0f, 0.0f,  0.03125f, 0.0625f * 5.0f,
    1.0f, 1.0f, 0.0f,  0.03125f, 0.0625f * 6.0f,
    0.0f, 1.0f, 0.0f,  0.0f,     0.0625f * 6.0f,

    // BACK (Z = 1)
    1.0f, 0.0f, 1.0f,  0.0f,     0.0625f * 5.0f,
    0.0f, 0.0f, 1.0f,  0.03125f, 0.0625f * 5.0f,
    0.0f, 1.0f, 1.0f,  0.03125f, 0.0625f * 6.0f,
    1.0f, 1.0f, 1.0f,  0.0f,     0.0625f * 6.0f,

    // LEFT (X = 0)
    0.0f, 0.0f, 1.0f,  0.0f,     0.0625f * 5.0f,
    0.0f, 0.0f, 0.0f,  0.03125f, 0.0625f * 5.0f,
    0.0f, 1.0f, 0.0f,  0.03125f, 0.0625f * 6.0f,
    0.0f, 1.0f, 1.0f,  0.0f,     0.0625f * 6.0f,

    // RIGHT (X = 1)
    1.0f, 0.0f, 0.0f,  0.0f,     0.0625f * 5.0f,
    1.0f, 0.0f, 1.0f,  0.03125f, 0.0625f * 5.0f,
    1.0f, 1.0f, 1.0f,  0.03125f, 0.0625f * 6.0f,
    1.0f, 1.0f, 0.0f,  0.0f,     0.0625f * 6.0f,

    // TOP (Y = 1)
    0.0f, 1.0f, 0.0f,  0.03125f * 3.0f, 0.0625f * 5.0f,
    1.0f, 1.0f, 0.0f,  0.03125f * 4.0f, 0.0625f * 5.0f,
    1.0f, 1.0f, 1.0f,  0.03125f * 4.0f, 0.0625f * 6.0f,
    0.0f, 1.0f, 1.0f,  0.03125f * 3.0f, 0.0625f * 6.0f,

    // DOWN (Y = 0)
    0.0f, 0.0f, 1.0f,  0.03125f * 8.0f, 0.0625f * 11.0f,
    1.0f, 0.0f, 1.0f,  0.03125f * 9.0f, 0.0625f * 11.0f,
    1.0f, 0.0f, 0.0f,  0.03125f * 9.0f, 0.0625f * 12.0f,
    0.0f, 0.0f, 0.0f,  0.03125f * 8.0f, 0.0625f * 12.0f,
};

unsigned int dirtIndices[] = {
    0, 1, 2,  2, 3, 0,     // FRONT
    4, 5, 6,  6, 7, 4,     // BACK
    8, 9, 10, 10, 11, 8,   // LEFT
    12, 13, 14, 14, 15, 12,// RIGHT
    16, 17, 18, 18, 19, 16,// TOP
    20, 21, 22, 22, 23, 20 // DOWN
};

Chunk chunk_create(void) {
    Chunk chunk;

    chunk.blocks = malloc(CHUNK_WIDTH * CHUNK_DEPTH * CHUNK_HEIGHT * sizeof(Block));
    if (!chunk.blocks) {
        printf("Error: Could not create chunk, not enough memory.\n");
        exit(-1);
    }

    // Default worldPos
    chunk.worldPos = (WorldPos){0, 0, 0}; 

    // Not built yet
    chunk.currentMesh = NULL;

    return chunk;
}

void chunk_build_mesh(Chunk *chunk) {
    if (chunk->currentMesh) {
        mesh_destroy(chunk->currentMesh);
    } else {
        chunk->currentMesh = malloc(sizeof(Mesh));
    }

    GLfloat *vertices = malloc(sizeof(GLfloat) * 120 * CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_DEPTH);
    GLuint *indices = malloc(sizeof(GLuint) * 36 * CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_DEPTH);
    unsigned int currentVertexIndex = 0;
    unsigned int currentIndiceIndex = 0;

    unsigned int solidBlocks = 0;

    for (uint8_t x = 0; x < CHUNK_WIDTH; ++x) {
        for (uint16_t y = 0; y < CHUNK_HEIGHT; ++y) {
            for (uint8_t z = 0; z < CHUNK_DEPTH; ++z) {
                if (chunk_get_block(chunk, (ivec3){x, y, z}) != BLOCK_AIR) {

                    // Copy the dirt vertice and translate it to world pos
                    for (int i = 0; i < 24; ++i) {
                        vertices[currentVertexIndex++] = x + dirtVertices[5 * i]; // X
                        vertices[currentVertexIndex++] = y + dirtVertices[5 * i + 1]; // Y
                        vertices[currentVertexIndex++] = z + dirtVertices[5 * i + 2]; // Z
                        vertices[currentVertexIndex++] = dirtVertices[5 * i + 3]; // U
                        vertices[currentVertexIndex++] = dirtVertices[5 * i + 4]; // V
                    }

                    // Copies the 
                    for (int i = 0; i < 36 ; ++i) {
                        indices[currentIndiceIndex++] = (solidBlocks * 24) + dirtIndices[i];
                    }

                    solidBlocks++;
                }
            }
        }
    }

    *chunk->currentMesh = mesh_init(vertices, indices, currentVertexIndex, currentIndiceIndex);
    free(vertices);
    free(indices);
}

void chunk_draw(Chunk *chunk) {
    mesh_draw(chunk->currentMesh);
}

void chunk_destroy(Chunk *chunk) {
    if (chunk->currentMesh) {
        mesh_destroy(chunk->currentMesh);
        free(chunk->currentMesh);
    }
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
}

inline WorldPos chunk_get_world_pos(Chunk *chunk) {
    return chunk->worldPos;
}

// Remove this in release probably
void chunk_fill_block(Chunk *chunk, Block desiredBlock) {
    // Don't know if uint8_t is premature optimization POV: It was LOL
    // But shall fit well
    for (uint8_t x = 0; x < CHUNK_WIDTH; ++x) {
        for (uint16_t y = 0; y < CHUNK_HEIGHT; ++y) {
            for (uint8_t z = 0; z < CHUNK_DEPTH; ++z) {
                chunk_set_block(chunk, desiredBlock, (ivec3){x, y, z});
            }
        }
    }
}