#ifndef VID_MEM_H
#define VID_MEM_H

#include <stdio.h>

#include "opengl/OpenGL.h"
#include "file-handling/log-writer/log-writer.h"
#include "file-handling/scene-files/scen-struct.h"
#include "tracer/camera/camera.h"

#define MAX_SHDR_VAR_LEN 32

/*
 *   INPUT  : Pointer to GL ID for texture. Width of texture to be created.
 *            Height of texture to be created.
 *   OUTPUT : -
 * 
 *   DESC   : Creates a GL texture.
 */
void create_texture(int *texture_id, int texture_width, int texture_height);

/*
 *   INPUT  : ID of compute shader program. Array of objects making the world.
 *            Number of objects in the world.
 *   OUTPUT : -
 *
 *   DESC   : Sets the data in `world` to the corresponding `world` array in
 *            the compute shader. Due to the data types being abstract, this
 *            involves a separate set for each property of each struct in the
 *            array.
 */
void set_world(int program_id, struct scene_obj world[MAX_OBJ_COUNT], int obj_c);

/*
 *   INPUT  : ID of compute shader program. Camera object to set for shader.
 *   OUTPUT : -
 * 
 *   DESC   : Sets the camera as described by `cam` to the corresponding `cam`
 *            object in the shader program.
 */
void set_camera(int program_id, struct camera cam);

/*
 *   INPUT  :  ID of compute shader program. Maximum number of bounces. Maximum
 *             number of samples.
 *   OUTPUT : -
 * 
 *   DESC   : Sets the two parameters max bounces and max samples in the shader
 *            program.
 */
void set_maxes(int program_id, int max_bounces, int max_samples);

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