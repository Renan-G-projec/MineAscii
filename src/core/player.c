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

    player.keyboardContext = keyboardContext;

    return player;
}

void player_update(Player *player) {
    // Temporary implementation
    // TODO: Make the camera just follow the player vision without updating it directly.

    if (keyboardctx_isKeyPressed(player->keyboardContext, 'W')) {
        glm_vec3_add(player->camera.orientation, player->camera.position, player->camera.position);
    }
    if (keyboardctx_isKeyPressed(player->keyboardContext, 'S')) {
        glm_vec3_negate(player->camera.orientation);
        glm_vec3_add(player->camera.orientation, player->camera.position, player->camera.position);
        glm_vec3_negate(player->camera.orientation);
    }
    if (keyboardctx_isKeyPressed(player->keyboardContext, 'A')) {
        vec3 horizontalAxis;
        glm_cross(player->camera.orientation, (vec3){0, 1, 0}, horizontalAxis);

        glm_vec3_negate(horizontalAxis);
        glm_vec3_add(horizontalAxis, player->camera.position, player->camera.position);
    }
    if (keyboardctx_isKeyPressed(player->keyboardContext, 'D')) {
        vec3 horizontalAxis;
        glm_cross(player->camera.orientation, (vec3){0, 1, 0}, horizontalAxis);
        
        glm_vec3_add(horizontalAxis, player->camera.position, player->camera.position);
    }

    float rotX = 0, rotY = 0;
    if (keyboardctx_isKeyPressed(player->keyboardContext, 'I')) {
        rotY += 10;
    }
if (keyboardctx_isKeyPressed(player->keyboardContext, 'K')) {
        rotY -= 10;
    }
    if (keyboardctx_isKeyPressed(player->keyboardContext, 'L')) {
        rotX += 10;
    }
    if (keyboardctx_isKeyPressed(player->keyboardContext, 'J')) {
        rotX -= 10;
    }

    vec3 axisToRotateY;
    glm_cross(player->camera.orientation, (vec3){0, 1, 0}, axisToRotateY);
    glm_vec3_rotate(player->camera.orientation, glm_rad(rotY), axisToRotateY);
    glm_vec3_rotate(player->camera.orientation, glm_rad(-rotX), (vec3){0, 1, 0});
}

void player_send_camera_matrix(Player *player, Shader sh) {
    camera_send_matrix(&player->camera, sh);
}