// Ad Maiorem Dei Gloriam!
#ifndef CAMERA_H
#define CAMERA_H

#include <cglm/cglm.h>

typedef struct {
    vec3 position;
    vec3 orientation;
} Camera;

extern Camera gCamera;

// Creates an camera and configures it
Camera camera_create(vec3 position);

// Locates the uniform "camMatrix" and sends the camera matrixf
void camera_send_matrix(Camera *);

#endif