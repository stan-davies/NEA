#include "vid-mem.h"

void create_texture(int *texture_id, int texture_width, int texture_height) {
        glGenTextures(1, texture_id);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, *texture_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, texture_width, texture_height, 0, GL_RGBA, GL_FLOAT, NULL);

        glBindImageTexture(0, *texture_id, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
}

void retrieve_texture(int img_width, int img_height, float **pixels) {
        *pixels = calloc(img_width * img_height, 4 * sizeof(float));
        glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_FLOAT, *pixels);
}