// Ad Maiorem Dei Gloriam!
#ifndef BLOCKS_H
#define BLOCKS_H

#define BLOCK_AIR 0
#define BLOCK_DIRT 1

#include <stdint.h>

typedef uint8_t Block;

typedef struct {
    int x;
    int y;
} UVint;

typedef struct {
    float u;
    float v;
} UV;

typedef enum {
    FRONT,
    BACK,
    TOP,
    BOTTOM,
    LEFT,
    RIGHT
} Direction;

// Get the coordinates to the defined block mapped on the atlas
UVint getTextureUv(Block block, Direction dir);

// Normalizes to UV coordinates
UV normalizeUVint(UVint uv);

#endif