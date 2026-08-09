// Ad Maiorem Dei Gloriam!
#include "core/blocks.h"

#define UNKNOWN_BLOCK (UVint){5, 1}

#define ATLAS_WIDTH 32
#define ATLAS_HEIGHT 16

// Formatted in this form
const UVint BLOCKS_UV[] = {
    // SIDES    // TOP      // BOTTOM
    {0, 5},     {4, 5},     {11, 8} // GRASS
};

UVint getTextureUv(Block block, Direction direction) {
    int8_t offset = 0;
    if (direction == TOP) offset = 1;
    if (direction == BOTTOM) offset = 1;

    unsigned int index = block * 3 + offset;
    if (index > sizeof(BLOCKS_UV) / sizeof(BLOCKS_UV[0])) return UNKNOWN_BLOCK;

    return BLOCKS_UV[index];
}

UV normalizeUVint(UVint uvInt) {
    float widthFactor = 1.0f / (float)ATLAS_WIDTH;
    float heightFactor = 1.0f / (float)ATLAS_HEIGHT;

    UV uv = {widthFactor * uvInt.x, heightFactor * uvInt.y};
    return uv;
}