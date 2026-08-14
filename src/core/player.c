// Ad Maiorem Dei Gloriam!
#include "core/player.h"

Player player_create(KeyboardCtx *keyboardContext) {
    Player player;

    // Really don't like how window ratio is passed here
    player.camera = camera_create((float)WINDOW_MODE_WIDTH / (float)WINDOW_MODE_HEIGHT);

    player.orientation[0] = 0;
    player.orientation[1] = 0;
    player.orientation[2] = -1;

    player.position[0] = 0;
    player.position[1] = 0;
    player.position[2] = 0;

    player.velocity[0] = 0;
    player.velocity[1] = 0;
    player.velocity[2] = 0;

    player.keyboardContext = keyboardContext;

    return player;
}

void player_update(Player *player) {
    player_update_velocity(player);
    player_update_position(player);
    player_update_orientation(player);
    player_update_camera(player);   
}

void player_update_velocity(Player *player) {
    player->velocity[0] = 0;
    player->velocity[2] = 0;

    if (keyboardctx_isKeyPressed(player->keyboardContext, 'W')) {
        // We copy the x and z directions
        player->velocity[0] = player->orientation[0] * PLAYER_DEFAULT_SPEED;
        player->velocity[2] = player->orientation[2] * PLAYER_DEFAULT_SPEED;
    }
    if (keyboardctx_isKeyPressed(player->keyboardContext, 'S')) {
        player->velocity[0] = -player->orientation[0] * PLAYER_DEFAULT_SPEED;
        player->velocity[2] = -player->orientation[2] * PLAYER_DEFAULT_SPEED;
    }
    if (keyboardctx_isKeyPressed(player->keyboardContext, 'D')) {
        vec3 horizontalAxis;
        glm_cross(player->orientation, (vec3){0, 1, 0}, horizontalAxis);

        player->velocity[0] = horizontalAxis[0] * PLAYER_DEFAULT_SPEED;
        player->velocity[2] = horizontalAxis[2] * PLAYER_DEFAULT_SPEED;
    }
    if (keyboardctx_isKeyPressed(player->keyboardContext, 'A')) {
        vec3 horizontalAxis;
        glm_cross(player->orientation, (vec3){0, 1, 0}, horizontalAxis);

        player->velocity[0] = -horizontalAxis[0] * PLAYER_DEFAULT_SPEED;
        player->velocity[2] = -horizontalAxis[2] * PLAYER_DEFAULT_SPEED;
    }
}

inline void player_update_position(Player *player) {
    glm_vec3_add(player->position, player->velocity, player->position);
}

void player_update_orientation(Player *player) {
    float rotX = 0, rotY = 0;
    if (keyboardctx_isKeyPressed(player->keyboardContext, 'I')) {
        rotY += 10 * PLAYER_SENSITIVITY;
    }
    if (keyboardctx_isKeyPressed(player->keyboardContext, 'K')) {
        rotY -= 10 * PLAYER_SENSITIVITY;
    }
    if (keyboardctx_isKeyPressed(player->keyboardContext, 'L')) {
        rotX += 10 * PLAYER_SENSITIVITY;
    }
    if (keyboardctx_isKeyPressed(player->keyboardContext, 'J')) {
        rotX -= 10 * PLAYER_SENSITIVITY;
    }

    vec3 axisToRotateY;
    glm_cross(player->orientation, (vec3){0, 1, 0}, axisToRotateY);
    glm_vec3_rotate(player->orientation, glm_rad(rotY), axisToRotateY);
    glm_vec3_rotate(player->orientation, glm_rad(-rotX), (vec3){0, 1, 0});
}

inline void player_update_camera(Player *player) {
    // This function will handle the case of the different camera states
    // For now, only the first person so only copies are made.
    glm_vec3_copy(player->position, player->camera.position);
    glm_vec3_copy(player->orientation, player->camera.orientation);
}

void player_send_camera_matrix(Player *player, Shader sh) {
    camera_send_matrix(&player->camera, sh);
}