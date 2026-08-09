// Ad Maiorem Dei Gloriam!
#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <cglm/cglm.h>

#include "graphics/shader.h"

typedef struct {
    vec3 position;
    vec3 orientation;
    float window_ratio;
} Camera;

// Creates an camera and configures it
Camera camera_create(float window_ratio);

// Locates the uniform "camMatrix" and sends the camera matrix
void camera_send_matrix(Camera *, Shader sh);

// Moves the camera to the position
inline void camera_set_pos(Camera *, float x, float y, float z);

#endif