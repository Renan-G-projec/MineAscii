// Ad Maiorem Dei Gloriam!
#include "core/chunk.h"

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
        free(chunk->currentMesh->indices);
        free(chunk->currentMesh->vertices);
        mesh_destroy(chunk->currentMesh);
    } 
}

void chunk_destroy(Chunk *chunk) {
    if (chunk->currentMesh) {
        free(chunk->currentMesh->indices);
        free(chunk->currentMesh->vertices);
        mesh_destroy(chunk->currentMesh);
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

    int index = x * CHUNK_WIDTH * CHUNK_HEIGHT + y * CHUNK_WIDTH + z;
    chunk->blocks[index] = block;
}

Block chunk_get_block(Chunk *chunk, ivec3 pos) {
    int x = pos[0];
    int y = pos[1];
    int z = pos[2];

    if (x < 0 || x >= CHUNK_WIDTH) return BLOCK_AIR;
    if (y < 0 || y >= CHUNK_HEIGHT) return BLOCK_AIR;
    if (z < 0 || z >= CHUNK_DEPTH) return BLOCK_AIR;

    int index = x * CHUNK_WIDTH * CHUNK_HEIGHT + y * CHUNK_WIDTH + z;
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
    // Don't know if uint8_t is premature optimization
    // But shall fit well
    for (uint8_t x = 0; x < CHUNK_WIDTH; ++x) {
        for (uint8_t y = 0; y < CHUNK_HEIGHT; ++y) {
            for (uint8_t z = 0; z < CHUNK_DEPTH; ++z) {
                chunk_set_block(chunk, desiredBlock, (ivec3){x, y, z});
            }
        }
    }
}