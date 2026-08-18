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
        if (hit) break;
        
        glm_vec3_add(rayStepVector, ray, ray);
        
        walkedDistance += step;
    }

    result.hit = hit;
    if (hit) {
        result.block[0] = (int)floorf(ray[0]);
        result.block[1] = (int)floorf(ray[1]);
        result.block[2] = (int)floorf(ray[2]);

        int differenceX = (int)floorf(ray[0]) - (int)floorf(ray[0] - rayStepVector[0]);
        int differenceY = (int)floorf(ray[1]) - (int)floorf(ray[1] - rayStepVector[1]);
        int differenceZ = (int)floorf(ray[2]) - (int)floorf(ray[2] - rayStepVector[2]);

        if (differenceX) {
            result.face = differenceX > 0 ? LEFT : RIGHT;
        } else if (differenceY) {
            result.face = differenceY > 0 ? BOTTOM : TOP;
        } else {
            result.face = differenceZ > 0 ? FRONT : BACK;
        }
    }

    return result;
}