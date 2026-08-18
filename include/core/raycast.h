// Ad Maiorem Dei Gloriam!
#ifndef RAYCAST_H
#define RAYCAST_H

#include <cglm/cglm.h>
#include "core/world.h"

typedef struct {
    ivec3 block;
    CubeFace face;
    bool hit;
} RaycastResult;

RaycastResult raycast_traceray(World * const world, vec3 rayOrigin, vec3 rayOrientation, const float step, const float maxRange);

#endif