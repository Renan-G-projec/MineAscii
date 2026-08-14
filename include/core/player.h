// Ad Maiorem Dei Gloriam!
#ifndef PLAYER_H
#define PLAYER_H

#include <glad/glad.h>
#include "configs.h"
#include "engine.h"
#include "graphics/input.h"
#include "graphics/camera.h"

typedef struct {
    Camera camera;
    vec3 position;
    vec3 orientation;

    // Context settings
    KeyboardCtx* keyboardContext;
} Player;

// Creates the player at default position {0, 0, 0}
Player player_create(KeyboardCtx *keyboardContext);

// Updates game Logic
void player_update(Player *);

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