// Ad Maiorem Dei Gloriam!
#include "util/worldChunkHashmap.h"

static inline unsigned int hash_world_pos(WorldPos worldPos)
{
    const unsigned long long k1 = 14020252567694004749ULL;
    const unsigned long long k2 = 9695998579374968831ULL;
    const unsigned long long k3 = 2860486313ULL;

    unsigned long long hash = k3;
    hash = (hash ^ (unsigned long long)worldPos.x) * k1;
    hash = (hash ^ (unsigned long long)worldPos.y) * k2;
    hash = (hash ^ (unsigned long long)worldPos.z) * k1;

    hash ^= hash >> 33;
    hash *= 0xff51afd7ed558ccdULL;
    hash ^= hash >> 33;

    return hash % NUM_BUCKETS;
}

inline bool world_pos_compare(WorldPos a, WorldPos b)
{
    return (a.x == b.x && a.y == b.y && a.z == b.z);
}

ChunkHashmap chunkhashmap_create()
{
    ChunkHashmap chunkHashmap;

    for (int i = 0; i < NUM_BUCKETS; ++i)
    {
        chunkHashmap.buckets[i] = NULL;
    }

    return chunkHashmap;
}

void chunkhashmap_clear(ChunkHashmap *chunkHashmap)
{
    for (int i = 0; i < NUM_BUCKETS; ++i)
    {
        struct ChunkHashmapNode *current = chunkHashmap->buckets[i];
        while (current)
        {
            chunk_destroy(&current->chunk);
            struct ChunkHashmapNode *next = current->next;
            current->next = NULL;
            free(current);
            current = next;
        }
        chunkHashmap->buckets[i] = NULL;
    }
}

Chunk *chunkhashmap_get(ChunkHashmap *chunkHashmap, WorldPos key)
{
    struct ChunkHashmapNode *node = chunkHashmap->buckets[hash_world_pos(key)];

    while (node)
    {
        if (world_pos_compare(key, node->key))
            return &node->chunk;
        node = node->next;
    }

    return NULL;
}

Chunk *chunkhashmap_set(ChunkHashmap *chunkHashmap, WorldPos key, Chunk chunk)
{
    unsigned int chunkNodeIndex = hash_world_pos(key);
    struct ChunkHashmapNode *node = chunkHashmap->buckets[chunkNodeIndex];

    struct ChunkHashmapNode *newOne = (struct ChunkHashmapNode *)malloc(sizeof(struct ChunkHashmapNode));
    newOne->chunk = chunk;
    newOne->key = key;
    newOne->next = node;

    chunkHashmap->buckets[chunkNodeIndex] = newOne;
    return &newOne->chunk;
};

void chunkhashmap_delete(ChunkHashmap *chunkHashmap, WorldPos key)
{
    struct ChunkHashmapNode *node = chunkHashmap->buckets[hash_world_pos(key)];

    while (node)
    {
        struct ChunkHashmapNode *parent = node;
        node = node->next;

        if (!node)
            return;

        if (world_pos_compare(key, node->key))
        {
            parent->next = node->next;
            chunk_destroy(&node->chunk);
            free(node);
            return;
        };
    }
}