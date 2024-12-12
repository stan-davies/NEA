#ifndef CAMERA_H
#define CAMERA_H

#include "global.h"
#include "file-handling/scene-files/scen-struct.h"
#include "file-handling/config-files/conf-struct.h"

#define PI 3.1415926535f

int create_camera(struct scene_obj *world, int obj_c, struct camera *cam, struct config_var *conf, int img_dims[2]);

inline float deg_to_rad(int angle);

// ONLY FOR USE WITH 3D
int unit(float **vec);

// ONLY FOR USE WITH 3D
inline float *scale(float *vec, float scl);

inline float *add(float *vec1, float *vec2);

inline void set(float **vec1, float *vec2);

struct camera {
        float pos[3];        // position of actual camera

        float plane_00[3];   // centre of top left pixel in viewing plane
        float plane_dx[3];   // unit vector parallel to base of viewing plane
        float plane_dy[3];   // unit vector parallel to height of viewing plane
};

#endif