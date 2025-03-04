#ifndef RENDER_CORE_H
#define RENDER_CORE_H

#include "tracer/shader-handling/comp-prog.h"
#include "tracer/shader-handling/vid-mem.h"
#include "tracer/image-writer/img-writer.h"
#include "tracer/prog-log/prog-log.h"
#include "tracer/camera/camera.h"
#include "file-handling/scene-files/scen-parser.h"

/*
 *   INPUT  : Vertical field of view of camera. Width of rendering frame.
 *            Height of rendering frame. Maximum number of samples per pixel. 
 *            Maximum number of bounces per ray. Ambient lighting coefficient. 
 *            Destination of output file. Destination of scene file.
 *   OUTPUT : Success in rendering.
 * 
 *   DESC   : Conducts the entire process of rendering. This involves many
 *            stages, so this function is really just a neat and sequential
 *            series of function calls.
 */
int render(float vfov, int img_width, int img_height, int max_samples, int max_bounces, float ambient_coef, char *output_file, char *scene_file);

#endif