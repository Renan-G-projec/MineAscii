// Ad Maiorem Dei Gloriam!
#include "core/blocks.h"

#define ATLAS_WIDTH 32
#define ATLAS_HEIGHT 16

#define WIDTH_FACTOR (1.0f / (float)ATLAS_WIDTH)
#define HEIGHT_FACTOR (1.0f / (float)ATLAS_HEIGHT)

typedef struct {
    int x, y;
} MappedPosition;

#define UNKNOWN_BLOCK ((MappedPosition){5, 1})

// Formatted in this form
static const MappedPosition BLOCKS_UV[] = {
    // SIDES    // TOP      // BOTTOM
    {0, 5},     {4, 5},     {11, 8} // GRASS
};

UV block_get_uv(Block block, CubeFace cubeFace, FaceCorner faceCorner) {
    UV uv;
    
    int mappedBlocks = sizeof(BLOCKS_UV) / 3;

    if (block > mappedBlocks) {
        uv.u = UNKNOWN_BLOCK.x * WIDTH_FACTOR;
        uv.v = UNKNOWN_BLOCK.y * HEIGHT_FACTOR;
    } else {
        block--; // We decrease in order to correct index manipulation. Air is block 0 and Dirt starts at 1.
        switch (cubeFace) {
            case TOP: {
                uv.u = BLOCKS_UV[block * 3 + 1].x * WIDTH_FACTOR;
                uv.v = BLOCKS_UV[block * 3 + 1].y * HEIGHT_FACTOR;
                break;
            }
            case BOTTOM: {
                uv.u = BLOCKS_UV[block * 3 + 2].x * WIDTH_FACTOR;
                uv.v = BLOCKS_UV[block * 3 + 2].y * HEIGHT_FACTOR;
                break;
            }
            default: {
                uv.u = BLOCKS_UV[block * 3].x * WIDTH_FACTOR;
                uv.v = BLOCKS_UV[block * 3].y * HEIGHT_FACTOR;
                break;
            }
        }
    }

    // Post processing
    switch (faceCorner) {
        case BOTTOM_LEFT: {
            break;
        }
        case TOP_LEFT: {
            uv.v += HEIGHT_FACTOR;
            break;
        }
        case BOTTOM_RIGHT: {
            uv.u += WIDTH_FACTOR;
            break;
        }
        case TOP_RIGHT: {
            uv.u += WIDTH_FACTOR;
            uv.v += HEIGHT_FACTOR;
            break;
        }
    }

    return uv;
}
