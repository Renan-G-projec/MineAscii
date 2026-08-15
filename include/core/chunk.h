// Ad Maiorem Dei Gloriam!
#ifndef CHUNK_H
#define CHUNK_H

// This will allocate 65kb, i do not like how it is implemented
// I need to optimize with chunk compression maybe
#define CHUNK_WIDTH 16
#define CHUNK_DEPTH 16
#define CHUNK_HEIGHT 256

// This macros are meant for chunk generation
#define CHUNK_BASE 120

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cglm/cglm.h>
#include <perlin.h>

#include "core/blocks.h"
#include "graphics/shader.h"
#include "graphics/mesh.h"

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} WorldPos;

typedef struct {
    Block *blocks;
    Mesh mesh;

    WorldPos worldPos;
    mat4 modelMat; // Only recalculated when the world pos is changed.
} Chunk;

// Initializes the chunk shader and gets the uniforms location
void chunk_init_shaders(Shader chunkShader);

// Initializes the chunk and allocates memory.
Chunk chunk_create(void);

// Builds the mesh of the chunk and maps the textures UV
void chunk_build_mesh(Chunk *); // NOT IMPLEMENTED YET

// Draws the chunk
void chunk_draw(Chunk *);

// Deletes and frees the memory
void chunk_destroy(Chunk *);

// Helper functions
void chunk_set_block(Chunk *, Block block, ivec3 coord); // Sets the block at the position. If outside the chunk, does nothing.
Block chunk_get_block(Chunk *, ivec3 coord); // Gets the block at the position. Returns air outside the chunk.

void chunk_set_world_pos(Chunk*, WorldPos coord); // Moves the chunk to the desired position.
WorldPos chunk_get_world_pos(Chunk *); // Gets the chunk's world position

// Generator
void chunk_generate(Chunk *, int seed);

// Debug functions
void chunk_fill_block(Chunk *, Block block);

#endif