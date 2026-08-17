// Ad Maiorem Dei Gloriam!
#include "core/raycast.h"

RaycastResult raycast_traceray(World * const world, vec3 rayOrigin, vec3 rayOrientation, const float step, const float maxRange) {
    RaycastResult result;
    float walkedDistance = 0;

    vec3 ray;
    glm_vec3_copy(rayOrigin, ray);

    vec3 rayStepVector;
    glm_vec3_scale(rayOrientation, step, rayStepVector);

    bool hit = false;
    while (!hit && walkedDistance <= maxRange) {
        hit = world_get_block(world, ray) != BLOCK_AIR;
        
        glm_vec3_add(rayStepVector, ray, ray);
        
        walkedDistance += step;
    }

    result.hit = hit;
    if (hit) {
        result.block[0] = (int)floorf(ray[0]);
        result.block[1] = (int)floorf(ray[1]);
        result.block[2] = (int)floorf(ray[2]);
    }

    return result;
}