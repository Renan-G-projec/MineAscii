// Ad Maiorem Dei Gloriam!
#include "core/world.h"

World world_create(int seed) {
    World world;

    world.seed = seed;
    world.chunks = (Chunk *)malloc(WORLD_CHUNKS * WORLD_CHUNKS * sizeof(Chunk));

    if (!world.chunks) {
        printf("Error: Could not generate world. Out of memory.\n");
        exit(-1);
    }

    for (int x = 0; x < WORLD_CHUNKS; ++x) {
        for (int z = 0; z < WORLD_CHUNKS; ++z) {
            int chunkIndex = x * WORLD_CHUNKS + z;
            world.chunks[chunkIndex] = chunk_create();
            chunk_set_world_pos(&(world.chunks[chunkIndex]), (WorldPos){x * CHUNK_WIDTH, -CHUNK_HEIGHT, z * CHUNK_DEPTH});
            chunk_generate(&(world.chunks[chunkIndex]), seed);
            chunk_build_mesh(&(world.chunks[chunkIndex]));
        }     
    }

    return world;
}

void world_draw(World *world) {
    for (int i = 0; i < (WORLD_CHUNKS * WORLD_CHUNKS); ++i) {
        chunk_draw(&world->chunks[i]);   
    }
}

void world_destroy(World *world) {
    if (!world->chunks) return;
    for (int i = 0; i < (WORLD_CHUNKS * WORLD_CHUNKS); ++i) {
        chunk_destroy(&world->chunks[i]);
    }
    free(world->chunks);
}