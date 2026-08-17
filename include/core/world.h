// Ad Mairoem Dei Gloriam!
#ifndef WORLD_H
#define WORLD_H

#include "core/chunk.h"

#define WORLD_CHUNKS 9

typedef struct {
    Chunk *chunks;
    
    int seed;
    Shader shader;
} World;

// Generates the world
World world_create(int seed);

// Draws all the chunks *I need to optimizze this*.
void world_draw(World *world);

// Frees the memory of all chunks
void world_destroy(World *world);

// Helpers
Block world_get_block(World *, vec3 coordinates);
Block world_get_block_i(World *, ivec3 coordinates);

void world_set_block(World *, Block block, vec3 coordinates);
void world_set_block_i(World *, Block block, ivec3 coordinates);

#endif