#include "camera.h"

int create_camera(struct scene_obj *world, int obj_c, struct camera *cam, struct config_var *conf) {
        int c_i;

        for (; c_i < obj_c; ++c_i) {
                if (CAMERA == world[c_i].type) {
                        break;
                }
        }

        if (c_i >= obj_c) {
                log_err("no camera in scene");
                return FALSE;
        }

        float *view_dir = malloc(3 * sizeof(float));

        for (int i = 0; i < 3; ++i) {
                cam->pos[i] = world[c_i].coords[i];
                view_dir[i] = world[c_i].dims[i] - cam->pos[i];
        }

        if (!unit(&view_dir)) {
                log_err("invalid viewing direction");
                return FALSE;
        }


        float focal_length = conf[FOCAL_LENGTH].flt;
        float vfov = deg_to_rad(1.f / focal_length);

        float *plane_cnt;

        plane_cnt = add(cam->pos, scale(view_dir, focal_length));

        float plane_h = 2.f * focal_length * tan(vfov);
        // this should be given?
        float *plane_j;
        set(&(cam->plane_dy), unit(plane_j / (float)conf[IMAGE_DIMS].i2[1]));

        float plane_w = plane_h * ((float)conf[IMAGE_DIMS].i2[0] / (float)conf[IMAGE_DIMS].i2[1]);
        float *plane_i;
        set(&(cam->plane_dx), unit(plane_i / (float)conf[IMAGE_DIMS].i2[0]));

        // currently does to the very top left of the viewing plane, not to the pixel centre
        set(&(cam->plane_00), add(plane_cnt, add(scale(plane_i, -0.5f), scale(plane_j, -0.5f))));

        return TRUE;
}

inline float deg_to_rad(int angle) {
        return angle * PI / 180.f;
}

int unit(float **vec) {
        float m = sqrt(
                (*vec)[0] * (*vec)[0] + 
                (*vec)[1] * (*vec)[1] + 
                (*vec)[2] * (*vec)[2]
        );

        if (0 == m) {
                return FALSE;
        }

        for (int i = 0; i < 3; ++i) {
                (*vec)[i] /= m;
        }

        return TRUE;
}

inline float *scale(float *vec, float scl) {
        for (int i = 0; i < 3; ++i) {
                vec[i] *= scl;
        }

        return vec;
}

inline float *add(float *vec1, float *vec2) {
        for (int i = 0; i < 3; ++i) {
                vec1[i] += vec2[i];
        }

        return vec1;
}

inline void set(float **vec1, float *vec2) {
        for (int i = 0; i < 3; ++i) {
                (*vec1)[i] = vec2[i];
        }
}