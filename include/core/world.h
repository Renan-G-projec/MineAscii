// Ad Mairoem Dei Gloriam!
#ifndef WORLD_H
#define WORLD_H

#include "core/chunk.h"

#define WORLD_CHUNKS 9

typedef struct {
    int seed;

    Chunk *chunks;
} World;

// Generates the world
World world_create(int seed);

// Draws all the chunks *I need to optimizze this*.
void world_draw(World *world);

// Frees the memory of all chunks
void world_destroy(World *world);

// Helpers
Block world_get_block(World *, vec3 coordinates);

#endif