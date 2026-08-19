// Ad Maiorem Dei Gloriam!
#ifndef WORLD_CHUNK_HASHMAP_H
#define WORLD_CHUNK_HASHMAP_H

#include "core/chunk.h"

#define NUM_BUCKETS 100

struct ChunkHashmapNode {
    WorldPos key;
    Chunk chunk;
    struct ChunkHashmapNode *next;
};

typedef struct {
    struct ChunkHashmapNode *buckets[NUM_BUCKETS];
} ChunkHashmap;

// Creates the chunk hashmap and returns it
ChunkHashmap chunkhashmap_create();

// Frees all the memory and sets every bucket to NULL
void chunkhashmap_clear(ChunkHashmap *);

// Gets the chunk by the world pos
Chunk *chunkhashmap_get(ChunkHashmap *, WorldPos key);

// Sets the chunk by the world pos. Returns the new chunk pointer
Chunk *chunkhashmap_set(ChunkHashmap *, WorldPos key, Chunk);

// Deletes the chunk
void chunkhashmap_delete(ChunkHashmap *, WorldPos key);

#endif