// Ad Maiorem Dei Gloriam!
#ifndef PLAYER_H
#define PLAYER_H

#include <glad/glad.h>
#include "graphics/camera.h"

typedef struct {
    Camera camera;
    vec3 position;
    vec3 orientation;
} Player;

// Creates the player at default position {0, 0, 0}
Player player_create(void);

// Updates game Logic
void player_update(Player *);

// Sends the camera matrix
void player_camera_send_matrix(Shader);

// Destroys and frees memory
void player_destroy(Player *);

// Changes the position while updating the camera
void player_set_position(Player *, vec3 newPos);
vec3 const * player_get_position(Player *);

// Changes the player and the camera
void player_set_orientation(Player *, float rotX, float rotY);
vec3 const * player_get_orientation(Player *, float rotX, float rotY);

#endif