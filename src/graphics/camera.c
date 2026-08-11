// Ad Maiorem Dei Gloriam!
#include "graphics/camera.h"

Camera camera_create(float window_ratio) {
    Camera c;
    c.position[0] = 0.0f;
    c.position[1] = 0.0f;
    c.position[2] = 0.0f;

    c.orientation[0] = 0.0f;
    c.orientation[1] = 0.0f;
    c.orientation[2] = 1.0f;

    c.window_ratio = window_ratio;
    
    return c;
}

void camera_send_matrix(Camera *cam, Shader sh) {
    mat4 view, projection, camMatrix;
    glm_mat4_identity(view);
    glm_mat4_identity(projection);
    glm_mat4_identity(camMatrix);

    // Sets the view matrix
    vec3 lookingPos;
    glm_vec3_add(cam->position, cam->orientation, lookingPos);
    vec3 up = {0, 1, 0};
    glm_translate(view, cam->position);
    glm_lookat(cam->position, lookingPos, up, view);

    // Sets the projection matrix
    glm_perspective(glm_rad(60.0f), cam->window_ratio, 0.001f, 100.0f, projection);

    glm_mat4_mul(projection, view, camMatrix);

    GLint uniformLocation = glGetUniformLocation(sh, "camMatrix");
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, camMatrix[0]);
}

inline void camera_set_pos(Camera *camera, float x, float y, float z) {
    camera->position[0] = x;
    camera->position[1] = y;
    camera->position[2] = x;
}