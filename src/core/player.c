// Ad Maiorem Dei Gloriam!
#include "core/player.h"

static inline float clamp(float min, float val, float max) {
    return (val > min ? (val < max ? val : max) : min);
}

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

    player.height = 2.0f;
    player.jumpForce = 0.7f;
    player.sensitivity = 0.4f;
    player.speed = 0.3f;


    player.onGround = false;


    return player;
}

void player_update(Player *player) {
    player_update_on_ground(player);
    player_update_velocity(player);
    player_snap_to_world(player);
    player_update_position(player);
    player_update_orientation(player);
    player_update_camera(player);   
}

void player_update_velocity(Player *player) {
    player->velocity[0] = 0;
    player->velocity[2] = 0;

    if (keyboardctx_isKeyPressed(player->keyboardContext, 'W')) {
        // We copy the x and z directions
        player->velocity[0] = player->orientation[0] * player->speed;
        player->velocity[2] = player->orientation[2] * player->speed;
    }
    if (keyboardctx_isKeyPressed(player->keyboardContext, 'S')) {
        player->velocity[0] = -player->orientation[0] * player->speed;
        player->velocity[2] = -player->orientation[2] * player->speed;
    }
    if (keyboardctx_isKeyPressed(player->keyboardContext, 'D')) {
        vec3 horizontalAxis;
        glm_cross(player->orientation, (vec3){0, 1, 0}, horizontalAxis);

        player->velocity[0] = horizontalAxis[0] * player->speed;
        player->velocity[2] = horizontalAxis[2] * player->speed;
    }
    if (keyboardctx_isKeyPressed(player->keyboardContext, 'A')) {
        vec3 horizontalAxis;
        glm_cross(player->orientation, (vec3){0, 1, 0}, horizontalAxis);

        player->velocity[0] = -horizontalAxis[0] * player->speed;
        player->velocity[2] = -horizontalAxis[2] * player->speed;
    }

    if (keyboardctx_isKeyPressed(player->keyboardContext, ' ') && player->onGround) {
        player_jump(player);
    }

    if (!player->onGround) {
        player->velocity[1] -= GRAVITY_DEFAULT;
    } else {
        player->velocity[1] = 0;
    }
}

inline void player_update_position(Player *player) {
    glm_vec3_add(player->position, player->velocity, player->position);
}

void player_snap_to_world(Player *player) {
    // To implemen
    if (player->onGround && player->velocity[1] < 0) player->position[1] = (int)(player->position[1]) + 1;
}

void player_update_orientation(Player *player) {
    float rotX = 0, rotY = 0;
    if (keyboardctx_isKeyPressed(player->keyboardContext, 'I')) {
        rotY += 10 * player->sensitivity;
    }
    if (keyboardctx_isKeyPressed(player->keyboardContext, 'K')) {
        rotY -= 10 * player->sensitivity;
    }
    if (keyboardctx_isKeyPressed(player->keyboardContext, 'L')) {
        rotX += 10 * player->sensitivity;
    }
    if (keyboardctx_isKeyPressed(player->keyboardContext, 'J')) {
        rotX -= 10 * player->sensitivity;
    }


    vec3 axisToRotateY;
    glm_cross(player->orientation, (vec3){0, 1, 0}, axisToRotateY);

    float upAngle = glm_vec3_angle((vec3){0, 1, 0}, player->orientation);

    if ((upAngle > 0.2 || rotY < 0) && (upAngle < 2.9 || rotY > 0)) glm_vec3_rotate(player->orientation, glm_rad(rotY), axisToRotateY);
    glm_vec3_rotate(player->orientation, glm_rad(-rotX), (vec3){0, 1, 0});
}

inline void player_update_camera(Player *player) {
    // This function will handle the case of the different camera states
    // For now, only the first person so only copies are made.
    glm_vec3_copy(player->position, player->camera.position);
    player->camera.position[1] += player->height;
    glm_vec3_copy(player->orientation, player->camera.orientation);
}

void player_send_camera_matrix(Player *player, Shader sh) {
    camera_send_matrix(&player->camera, sh);
}

void player_update_on_ground(Player *player) {
    vec3 nextPosition;
    glm_vec3_copy(player->position, nextPosition);
    nextPosition[1] -= 0.2f;
    
    player->onGround = (world_get_block(player->worldContext, nextPosition) != BLOCK_AIR);
    return;
}

inline void player_jump(Player *player) {
    player->velocity[1] = player->jumpForce;
    player->onGround = false;
}

inline void player_set_position(Player *player, vec3 newPosition) {
    glm_vec3_copy(newPosition, player->position);
    player_update_camera(player);
}