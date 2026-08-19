// Ad Maiorem Dei Gloriam!
#include "core/world.h"

static GLuint modelLocation;

static inline int floor_div(int a, int b) {
    return (a < 0) ? ((a - b + 1) / b) : (a/b);
}

static inline int floor_mod(int a, int b) {
    int mod = a % b;
    return mod < 0 ? mod + b : mod;
}

// Helps trackign if a chunk should be rendered
static inline bool chunk_shall_be_rendered(WorldPos renderPosition, WorldPos chunkPosition, short renderDistance) {
    bool overlapsOnX = chunkPosition.x >= (renderPosition.x - renderDistance) && chunkPosition.x <= (renderPosition.x + renderDistance);
    bool overlapsOnZ = chunkPosition.z >= (renderPosition.z - renderDistance) && chunkPosition.z <= (renderPosition.z + renderDistance);

    return overlapsOnX && overlapsOnZ;
}


World world_create(int seed) {
    World world;

    world.seed = seed;
    world.shader = shader_create("./assets/shaders/main.vert", "./assets/shaders/main.frag");
    shader_bind(world.shader);

    memset(world.loadedChunks, 0, sizeof(world.loadedChunks));
    world.chunkMap = chunkhashmap_create();
    
    world_load_new_chunks(&world, (WorldPos){0, 0, 0});

    GLint uTex0 = glGetUniformLocation(world.shader, "tex0");
    glUniform1i(uTex0, 0);

    modelLocation = glGetUniformLocation(world.shader, "modelMatrix");

    return world;
}

void world_draw(World *world) {
    shader_bind(world->shader);
    for (int i = 0; i < (WORLD_RENDER_DISTANCE * 4 * WORLD_RENDER_DISTANCE); ++i) {
        chunk_draw(world->loadedChunks[i], modelLocation);   
    }
}

// TODO: Improve readbility and unload older chunks

void world_load_new_chunks(World *world, WorldPos position) {

    for (int x = -WORLD_RENDER_DISTANCE; x < WORLD_RENDER_DISTANCE; ++x) {
        for (int z = -WORLD_RENDER_DISTANCE; z < WORLD_RENDER_DISTANCE; ++z) {
            int index = (x + WORLD_RENDER_DISTANCE) * 2 * WORLD_RENDER_DISTANCE + (z + WORLD_RENDER_DISTANCE);
            Chunk *chunk = world->loadedChunks[index];
            if (!chunk) continue;
            if (!chunk_shall_be_rendered(world->loadedChunksPosition, chunk->worldPos, WORLD_RENDER_DISTANCE)) {
                chunkhashmap_delete(&world->chunkMap, chunk->worldPos);
            };
        }
    }

    for (int x = -WORLD_RENDER_DISTANCE; x < WORLD_RENDER_DISTANCE; ++x) {
        for (int z = -WORLD_RENDER_DISTANCE; z < WORLD_RENDER_DISTANCE; ++z) {
            Chunk *currentChunk = chunkhashmap_get(&world->chunkMap, (WorldPos){x * CHUNK_WIDTH, 0, z * CHUNK_DEPTH});
            if (!currentChunk) {
                Chunk chunk = chunk_create();
                chunk_set_world_pos(&chunk, (WorldPos){x, 0, z});
                currentChunk = chunkhashmap_set(&world->chunkMap, chunk_get_world_pos(&chunk), chunk);
                chunk_generate(currentChunk, world->seed);
                chunk_build_mesh(currentChunk);
            }

            int index = (x + WORLD_RENDER_DISTANCE) * 2 * WORLD_RENDER_DISTANCE + (z + WORLD_RENDER_DISTANCE);
            world->loadedChunks[index] = currentChunk;
        }
    }

    world->loadedChunksPosition = position;
}

void world_destroy(World *world) {
    chunkhashmap_clear(&world->chunkMap);
    shader_destroy(world->shader);
}

inline Block world_get_block(World *world, vec3 coords) {
    return world_get_block_i(world, (ivec3){floorf(coords[0]), floorf(coords[1]), floorf(coords[2])});
}

Block world_get_block_i(World *world, ivec3 coords) {
    WorldPos chunkPos = {
        floor_div(coords[0], CHUNK_WIDTH),
        0, 
        floor_div(coords[2], CHUNK_DEPTH)
    };
    Chunk *chunk = chunkhashmap_get(&world->chunkMap, chunkPos);
    if (!chunk) return BLOCK_AIR;

    int localX, localY, localZ;
    localX = floor_mod(coords[0], CHUNK_WIDTH);
    localY = (coords[1]);
    localZ = floor_mod(coords[2], CHUNK_DEPTH);

    ivec3 localCoords = {localX, localY, localZ};
    
    return chunk_get_block(chunk, localCoords);
}

inline void world_set_block(World *world, Block block, vec3 coords) {
    world_set_block_i(world, block, (ivec3){floorf(coords[0]), floorf(coords[1]), floorf(coords[2])});
}

void world_set_block_i(World *world, Block block, ivec3 coords) {
    WorldPos chunkPos = {
        floor_div(coords[0], CHUNK_WIDTH),
        0, 
        floor_div(coords[2], CHUNK_DEPTH)
    };
    Chunk *chunk = chunkhashmap_get(&world->chunkMap, chunkPos);
    if (!chunk) return;

    int localX, localY, localZ;
    localX = floor_mod(coords[0], CHUNK_WIDTH);
    localY = (coords[1]);
    localZ = floor_mod(coords[2], CHUNK_DEPTH);

    ivec3 localCoords = {localX, localY, localZ};
    
    chunk_set_block(chunk, block, localCoords);
    chunk_build_mesh(chunk);
}