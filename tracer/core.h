#ifndef RENDER_CORE_H
#define RENDER_CORE_H

#include "tracer/shader-handling/comp-prog.h"
#include "tracer/shader-handling/vid-mem.h"
#include "tracer/image-writer/img-writer.h"
#include "tracer/prog-log/prog-log.h"
#include "tracer/camera/camera.h"
#include "file-handling/scene-files/scen-parser.h"

// default configuration
#define DEF_FOCAL_LENGTH 20.f
#define DEF_IMG_WIDTH    100
#define DEF_IMG_HEIGHT   100

int render(float focal_length, int img_width, int img_height);

#endif