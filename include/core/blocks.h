// Ad Maiorem Dei Gloriam!
#ifndef BLOCKS_H
#define BLOCKS_H

#define BLOCK_AIR 0
#define BLOCK_DIRT 1

#include <stdint.h>

typedef uint8_t Block;

// Defines the face of the cube on the 3 dimensional space
// Represents 4 vertices each one
typedef enum {
    FRONT,
    BACK,
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
} CubeFace;

// Each one represents a vertex
typedef enum {
    BOTTOM_LEFT,
    TOP_LEFT,
    BOTTOM_RIGHT,
    TOP_RIGHT
} FaceCorner;

typedef struct {
    GLfloat u, v;
} UV;

UV block_get_uv(Block block, CubeFace direction, FaceCorner corner);

#endif