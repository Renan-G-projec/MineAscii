// Ad Maiorem Dei Gloriam!
#include "core/player.h"

static inline float clamp(float min, float val, float max)
{
    return (val > min ? (val < max ? val : max) : min);
}

// The cube that marks the block the blayer is looking at
// Marked static so it will go to the global scope, not making the code awful
static GLfloat cube_vertices[] = {
    0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, // Vertices on the x axis
    0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, // Vertices on the y axis
    0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1  // Vertices on the z axis
};

static bool initializedHighlightCube = false;
static Shader highlightCubeShader = 0;
static VBO highlightCubeVBO = 0;
static VAO highlightCubeVAO = 0;

static GLuint highlightCubeModelMatUniform = 0;

static void initHightlightCube(void)
{
    highlightCubeVAO = vao_create();
    vao_bind(highlightCubeVAO);
    highlightCubeVBO = vbo_create();
    vbo_bind(highlightCubeVBO);

    vbo_set_data(highlightCubeVBO, sizeof(cube_vertices), cube_vertices);
    vao_define(0, 3, GL_FLOAT, 3 * sizeof(GLfloat), (void *)0);

    vao_unbind();
    vbo_unbind();

    highlightCubeShader = shader_create("./assets/shaders/highlightCube.vert", "./assets/shaders/highlightCube.frag");
    shader_bind(highlightCubeShader);

    highlightCubeModelMatUniform = glGetUniformLocation(highlightCubeShader, "modelMatrix");

    initializedHighlightCube = true;
    glLineWidth(5.f);
}

static void drawHighlightCube(Player *player)
{
    shader_bind(highlightCubeShader);
    vao_bind(highlightCubeVAO);
    player_send_camera_matrix(player, highlightCubeShader);

    mat4 cubeMat;
    glm_mat4_identity(cubeMat);
    glm_translate(cubeMat, (vec3){player->lookingAt.block[0], player->lookingAt.block[1], player->lookingAt.block[2]});

    glUniformMatrix4fv(highlightCubeModelMatUniform, 1, GL_FALSE, cubeMat[0]);

    glDrawArrays(GL_LINES, 0, 24);
}

static void destroyHighlightCube(void)
{
    vbo_destroy(highlightCubeVBO);
    vao_destroy(highlightCubeVAO);
    initializedHighlightCube = false;
}

Player player_create(KeyboardCtx *keyboardContext, World *world)
{
    Player player;

    // Really don't like how window ratio is passed here
    player.camera = camera_create((float)WINDOW_MODE_WIDTH / (float)WINDOW_MODE_HEIGHT);

    player.lookingAt.hit = 0;

    player.orientation[0] = 0;
    player.orientation[1] = 0;
    player.orientation[2] = -1;
    player.worldContext = world;

    
    player.position[0] = 0;
    player.position[1] = 0;
    player.position[2] = 0;
    
    player.velocity[0] = 0;
    player.velocity[1] = 0;
    player.velocity[2] = 0;
    
    player.chunk = world_get_chunk_coords(player.worldContext, player.position);
    
    player.keyboardContext = keyboardContext;

    player.height = 2.0f;
    player.jumpForce = 0.7f;
    player.sensitivity = 0.4f;
    player.speed = 0.3f;
    player.blockRange = 4.0f;

    player.onGround = false;

    player.input = (PlayerInput){0};

    if (!initializedHighlightCube)
        initHightlightCube();
    return player;
}

void player_draw(Player *player)
{
    if (player->lookingAt.hit)
        drawHighlightCube(player);
}

void player_update(Player *player)
{
    player_update_input(player);
    player_update_on_ground(player);
    player_update_velocity(player);
    player_snap_to_world(player);
    player_update_position(player);
    player_raycast(player);
    player_update_orientation(player);
    player_update_camera(player);
    player_update_chunk(player);
}

void player_update_input(Player *player) {
    player->input.forward = keyboardctx_isKeyPressed(player->keyboardContext, 'W');
    player->input.backward = keyboardctx_isKeyPressed(player->keyboardContext, 'S');
    player->input.leftward = keyboardctx_isKeyPressed(player->keyboardContext, 'A');
    player->input.rightward = keyboardctx_isKeyPressed(player->keyboardContext, 'D');

    player->input.jump = keyboardctx_isKeyPressed(player->keyboardContext, ' ');
    player->input.breakBlock = keyboardctx_isKeyPressed(player->keyboardContext, 'Q');
    player->input.putBlock = keyboardctx_isKeyPressed(player->keyboardContext, 'E');
}

void player_update_velocity(Player *player)
{
    player->velocity[0] = 0;
    player->velocity[2] = 0;

    if (player->input.forward)
    {
        // We copy the x and z directions
        player->velocity[0] = player->orientation[0] * player->speed;
        player->velocity[2] = player->orientation[2] * player->speed;
    }
    if (player->input.backward)
    {
        player->velocity[0] = -player->orientation[0] * player->speed;
        player->velocity[2] = -player->orientation[2] * player->speed;
    }
    if (player->input.rightward)
    {
        vec3 horizontalAxis;
        glm_cross(player->orientation, (vec3){0, 1, 0}, horizontalAxis);

        player->velocity[0] = horizontalAxis[0] * player->speed;
        player->velocity[2] = horizontalAxis[2] * player->speed;
    }
    if (player->input.leftward)
    {
        vec3 horizontalAxis;
        glm_cross(player->orientation, (vec3){0, 1, 0}, horizontalAxis);

        player->velocity[0] = -horizontalAxis[0] * player->speed;
        player->velocity[2] = -horizontalAxis[2] * player->speed;
    }

    if (player->input.jump && player->onGround)
    {
        player_jump(player);
    }

    if (player->input.breakBlock && player->lookingAt.hit)
    {
        world_set_block_i(player->worldContext, BLOCK_AIR, player->lookingAt.block);
    }

    if (player->input.putBlock && player->lookingAt.hit)
    {
        ivec3 direction;
        glm_ivec3_copy(player->lookingAt.block, direction);

        direction[0] += (player->lookingAt.face == RIGHT ? 1 : (player->lookingAt.face == LEFT ? -1 : 0));
        direction[1] += (player->lookingAt.face == TOP ? 1 : (player->lookingAt.face == BOTTOM ? -1 : 0));
        direction[2] += (player->lookingAt.face == BACK ? 1 : (player->lookingAt.face == FRONT ? -1 : 0));

        world_set_block_i(player->worldContext, BLOCK_GRASS, direction);
    }

    if (!player->onGround)
    {
        player->velocity[1] -= GRAVITY_DEFAULT;
    }
    else
    {
        player->velocity[1] = 0;
    }
}

inline void player_update_position(Player *player)
{
    glm_vec3_add(player->position, player->velocity, player->position);
}

void player_snap_to_world(Player *player)
{
    // To implemen
    if (player->onGround && player->velocity[1] < 0)
        player->position[1] = (int)(player->position[1]) + 1;
}

void player_update_orientation(Player *player)
{
    float rotX = 0, rotY = 0;
    if (keyboardctx_isKeyPressed(player->keyboardContext, 'I'))
    {
        rotY += 10 * player->sensitivity;
    }
    if (keyboardctx_isKeyPressed(player->keyboardContext, 'K'))
    {
        rotY -= 10 * player->sensitivity;
    }
    if (keyboardctx_isKeyPressed(player->keyboardContext, 'L'))
    {
        rotX += 10 * player->sensitivity;
    }
    if (keyboardctx_isKeyPressed(player->keyboardContext, 'J'))
    {
        rotX -= 10 * player->sensitivity;
    }

    vec3 axisToRotateY;
    glm_cross(player->orientation, (vec3){0, 1, 0}, axisToRotateY);

    float upAngle = glm_vec3_angle((vec3){0, 1, 0}, player->orientation);

    if ((upAngle > 0.2 || rotY < 0) && (upAngle < 2.9 || rotY > 0))
        glm_vec3_rotate(player->orientation, glm_rad(rotY), axisToRotateY);
    glm_vec3_rotate(player->orientation, glm_rad(-rotX), (vec3){0, 1, 0});
}

inline void player_update_camera(Player *player)
{
    // This function will handle the case of the different camera states
    // For now, only the first person so only copies are made.
    glm_vec3_copy(player->position, player->camera.position);
    player->camera.position[1] += player->height;
    glm_vec3_copy(player->orientation, player->camera.orientation);
}

void player_send_camera_matrix(Player *player, Shader sh)
{
    camera_send_matrix(&player->camera, sh);
}

void player_update_on_ground(Player *player)
{
    vec3 nextPosition;
    glm_vec3_copy(player->position, nextPosition);
    nextPosition[1] -= 0.2f;

    player->onGround = (world_get_block(player->worldContext, nextPosition) != BLOCK_AIR);
    return;
}

// Nothing is allocated in the player itself at the time
void player_destroy(Player *player)
{
    if (initializedHighlightCube)
        destroyHighlightCube();
    return;
}

inline void player_jump(Player *player)
{
    player->velocity[1] = player->jumpForce;
    player->onGround = false;
}

inline void player_set_position(Player *player, vec3 newPosition)
{
    glm_vec3_copy(newPosition, player->position);
    player->chunk = world_get_chunk_coords(player->worldContext, player->position);
    player_update_camera(player);
}

void player_update_chunk(Player *player) {
    WorldPos currentChunk = world_get_chunk_coords(player->worldContext, player->position);

    if (!world_pos_compare(currentChunk, player->chunk)) {
        player->chunk = currentChunk;
        world_load_new_chunks(player->worldContext, player->chunk);
    }
}

void player_raycast(Player *player)
{
    RaycastResult result = raycast_traceray(player->worldContext, (vec3){player->position[0], player->position[1] + player->height, player->position[2]}, player->orientation, 0.1f, 4.0f);
    player->lookingAt.hit = result.hit;
    player->lookingAt.face = result.face; 
    player->lookingAt.block[0] = result.block[0];
    player->lookingAt.block[1] = result.block[1];
    player->lookingAt.block[2] = result.block[2];
}