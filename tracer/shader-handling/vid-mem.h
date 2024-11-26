#ifndef VID_MEM_H
#define VID_MEM_H

#include <stdio.h>

#include "opengl/OpenGL.h"
#include "file-handling/log-writer/log-writer.h"

/*
 *   INPUT  : Pointer to GL ID for texture. Width of texture to be created.
 *            Height of texture to be created.
 *   OUTPUT : -
 * 
 *   DESC   : Creates a GL texture.
 */
void create_texture(int *texture_id, int texture_width, int texture_height);

/*
 *   INPUT  : Width of image. Height of image. Pointer to array of bytes for 
 *            pixel data.
 *   OUTPUT : -
 * 
 *   DESC   : Reads pixels from memory and puts them in `pixels` in RGBA8
 *            format.
 */
void retrieve_texture(int img_width, int img_height, float **pixels);

#endif