#include "vid-mem.h"

void create_texture(int *texture_id, int texture_width, int texture_height) {
        glGenTextures(1, texture_id);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, *texture_id);

        // tex paramter stuff, not needed?

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_width, texture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glBindImageTexture(0, *texture_id, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
}

// GL_READ_WRITE was set!
void render_texture(int texture_id) {
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

        glBindTexture(GL_TEXTURE_2D, texture_id);

        glFlush();
        glDisable(GL_TEXTURE_2D);

        int framebuffer_id;
        glGenFrameBuffers(1, &framebuffer_id);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_id);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);
}

void retrieve_texture(int texture_width, int texture_height, unsigned char **pixels) {
        *pixels = malloc(texture_width * texture_height * 3 * sizeof(unsigned char));

        glReadBuffer(GL_COLOR_ATTACHMENT0);
        glReadPixels(0, 0, texture_width, texture_height, GL_RGB, GL_UNSIGNED_BYTE, *pixels);
}