// Ad Maiorem Dei Gloriam!
#ifndef HITBOX_H
#define HITBOX_H

#include <cglm/cglm.h>

typedef struct {
    vec3 start;
    vec3 size;
    vec3 origin; // Defines the relative position that the hitbox will be moved or calculated collisions. Default is 0, 0, 0.
} Hitbox;

Hitbox hitbox_create(vec3 start, vec3 size);
void hitbox_set_origin(Hitbox *, vec3 origin);

// Given 3 hitboxes, calculates if those are colliding
void hitbox_check_collision(Hitbox *a, Hitbox *b);

// Helper function that moves the hitbox by its position
void hitbox_move(Hitbox *, vec3);

// Another helper that sets the absolute position
void hitbox_set_position(Hitbox *, vec3 newPos);

#endif