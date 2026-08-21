// Ad Maiorem Dei Gloriam!
#include "core/hitbox.h"

Hitbox hitbox_create(vec3 position, vec3 size) {
    Hitbox h;

    glm_vec3_copy(position, h.position);
    glm_vec3_copy(size, h.size);
    glm_vec3_copy((vec3){0.0f, 0.0f, 0.0f}, h.origin);
    return h;
}

inline void hitbox_set_origin(Hitbox *hitbox, vec3 origin) {
    glm_vec3_copy(origin, hitbox->origin);
}

bool hitbox_check_collision(Hitbox *a, Hitbox *b) {
    vec3 aEnd, bEnd;
    glm_vec3_add(a->position, a->size, aEnd);
    glm_vec3_add(b->position, b->size, bEnd);

    vec3 aBox[2], bBox[2];

    glm_vec3_copy(a->position, aBox[0]);
    glm_vec3_copy(aEnd, aBox[1]);

    glm_vec3_copy(b->position, bBox[0]);
    glm_vec3_copy(bEnd, bBox[1]);

    return glm_aabb_aabb(aBox, bBox);
}

inline void hitbox_move(Hitbox *hitbox, vec3 movement) {
    glm_vec3_add(hitbox->position, movement, hitbox->position);
}

inline void hitbox_set_position(Hitbox *hitbox, vec3 newPos) {
    glm_vec3_copy(newPos, hitbox->position);
    glm_vec3_sub(hitbox->position, hitbox->origin, hitbox->position);
}
