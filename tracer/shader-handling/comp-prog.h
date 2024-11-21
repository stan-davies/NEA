#ifndef COMP_PROG_H
#define COMP_PROG_H

#include "opengl/OpenGL.h"
#include "file-handling/shader-files/shad-parser.h"
#include "file-handling/log-writer/log-writer.h"

#define SHADER_DIR "tracer/shaders/"

/*
 *   INPUT  : Pointer for GL program ID.
 *   OUTPUT : Success in creating program.
 *
 *   DESC   : Creates a GL shader program containing 1 compute shader and
 *            checks that this creation was successful.
 */
int create_comp_program(int *program_id);

/*
 *   INPUT  : GL program ID to run. Width of wrok groups to dispatch. Height of
 *            work groups to dispatch.
 *   OUTPUT : -
 *
 *   DESC   : Dispatches the given compute shader program. The given work group
 *            dimensions should match the width and height of the output image.
 *            Then, if theh depth of the work group is 1, there is a single
 *            worker for each pixel, which is really the best we are going to
 *            get. It literally cannot get any better than each pixel being
 *            calculated on a separate thread. Is that not ridiculously cool?
 *            That is ridiculously cool.
 */
void run_comp_program(int program_id, int groups_x, int groups_y);

#endif