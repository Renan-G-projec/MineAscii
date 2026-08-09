// Ad Maiorem Dei Gloriam!
#ifndef CHUNK_H
#define CHUNK_H

#define CHUNK_WIDTH 16
#define CHUNK_DEPTH 16
#define CHUNK_HEIGHT 256

#include <stdint.h>
#include <cglm/cglm.h>
#include "core/blocks.h"
#include "graphics/mesh.h"

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} WorldPos;

typedef struct {
    Block *blocks;
    Mesh *currentMesh;

    vec3 worldPos;
} Chunk;

// Initializes the chunk and allocates memory.
Chunk chunk_create(void);

// Builds the mesh of the chunk and maps the textures UV
void chunk_build_mesh(Chunk *);

// Draws the chunk
void chunk_draw(Chunk *);

// Deletes and frees the memory
void chunk_destroy(Chunk *);

// These helper functions allow zero-cost abstractions.
inline void chunk_set_block(Chunk *, Block block, ivec3 coord);
inline Block chunk_get_block(Chunk *, ivec3 coord);
inline void chunk_set_world_pos(Chunk*, WorldPos coord);
inline WorldPos chunk_get_world_pos(Chunk *);

// Debug functions
void chunk_fill_block(Chunk *, Block block);

#endif