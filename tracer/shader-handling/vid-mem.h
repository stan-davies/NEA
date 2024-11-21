#ifndef VID_MEM_H
#define VID_MEM_H

#include <stdio.h>

#include "opengl/OpenGL.h"

/*
 *   INPUT  : Pointer to GL ID for texture. Width of texture to be created.
 *            Height of texture to be created.
 *   OUTPUT : -
 * 
 *   DESC   : Creates a GL texture.
 */
void create_texture(int *texture_id, int texture_width, int texture_height);

/*
 *   INPUT  : GL ID for texture to render.
 *   OUTPUT : -
 * 
 *   DESC   : Renders texture to framebuffer.
 */
void render_texture(int texture_id);

/*
 *   INPUT  : Width of texture. Height of texture. Pointer to array of bytes
 *            pixel data.
 *   OUTPUT : -
 * 
 *   DESC   : Reads pixels from buffer to which computed image was written.
 *            Requires call to `render_texture` for buffer to be populated.
 */
void retrieve_texture(int texture_width, int texture_height, unsigned char **pixels);

#endif