// Ad Maiorem Dei Gloriam!
#ifndef PLAYER_H
#define PLAYER_H

#include <glad/glad.h>
#include "core/world.h"
#include "configs.h"
#include "engine.h"
#include "graphics/input.h"
#include "graphics/camera.h"


typedef struct {
    ivec3 block;
    bool hit;
} RaycastResult;

typedef struct {
    Camera camera;
    RaycastResult lookingAt;
    
    vec3 position;
    vec3 orientation;

    // Speed settings
    vec3 velocity;

    // Context settings
    KeyboardCtx* keyboardContext;
    World *worldContext;

    // Configs
    float height; // Defines the heioght of the camera target. Points to the 'head'
    float jumpForce;
    float sensitivity;
    float speed; // Not the actual velocity. The speed multiplier.
    float blockRange; // Defines how far the player can destroy or put blocks

    // Flags
    bool onGround;
} Player;

// Creates the player at default position {0, 0, 0}
Player player_create(KeyboardCtx *keyboardContext);

// Updates game Logic
void player_update(Player *);

// Draws the player and anything related to it
void player_draw(Player *);

// Sub helper functions
void player_update_orientation(Player *);
void player_update_velocity(Player *);
void player_update_position(Player *);
void player_snap_to_world(Player *player);
void player_update_camera(Player *);
void player_update_on_ground(Player *);
void player_jump(Player *);

// Drawing functions
void player_raycast(Player *);

// Sends the camera matrix
void player_send_camera_matrix(Player *, Shader);

// Destroys and frees memory
void player_destroy(Player *);

// Changes the position while updating the camera
void player_set_position(Player *, vec3 newPos);
vec3 const * player_get_position(Player *);

// Changes the player and the camera
void player_set_orientation(Player *, float rotX, float rotY);
vec3 const * player_get_orientation(Player *, float rotX, float rotY);

#endif