// Ad Mairoem Dei Gloriam!
#ifndef WORLD_H
#define WORLD_H

#include "core/chunk.h"

#define WORLD_CHUNKS 9

typedef struct {
    int seed;

    Chunk *chunks;
} World;

World world_create(int seed);
void world_draw(World *world);
void world_destroy(World *world);

#endif