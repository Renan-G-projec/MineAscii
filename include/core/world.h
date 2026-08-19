// Ad Mairoem Dei Gloriam!
#ifndef WORLD_H
#define WORLD_H

#include <string.h>
#include "core/chunk.h"
#include "util/worldChunkHashmap.h"

#define WORLD_CHUNKS 9
#define WORLD_RENDER_DISTANCE 4

typedef struct {
    Chunk *loadedChunks[WORLD_RENDER_DISTANCE * 4 * WORLD_RENDER_DISTANCE];
    ChunkHashmap chunkMap;
    WorldPos loadedChunksPosition;
    
    int seed;
    Shader shader;
} World;

// Generates the world
World world_create(int seed);

// Draws all the chunks *I need to optimizze this*.
void world_draw(World *world);

// Updates the loaded chunks based on the position
void world_load_new_chunks(World *world, WorldPos position);

// Frees the memory of all chunks
void world_destroy(World *world);

// Helpers
Block world_get_block(World *, vec3 coordinates);
Block world_get_block_i(World *, ivec3 coordinates);

void world_set_block(World *, Block block, vec3 coordinates);
void world_set_block_i(World *, Block block, ivec3 coordinates);

#endif