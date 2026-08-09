// Ad Maiorem Dei Gloriam!
#include "graphics/texture.h"

Texture texture_create(void) {
    Texture t;
    glGenTextures(1, &t);

    return t;
}

void texture_load_png(Texture t, const char *filename) {
    int imgWidth, imgHeight, numColorChannels;
    stbi_set_flip_vertically_on_load(1);
    unsigned char *bytes = stbi_load(filename, &imgWidth, &imgHeight, &numColorChannels, 0);

    texture_bind(t);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    stbi_image_free(bytes);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glGenerateMipmap(GL_TEXTURE_2D);

    texture_unbind();
}

void texture_bind(Texture t) {
    glBindTexture(GL_TEXTURE_2D, t);
}

void texture_unbind(void) {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void texture_destroy(Texture t) {
    glDeleteTextures(1, &t);
}