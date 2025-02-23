#include "camera.h"

float vup[3] = { 0.f, 1.f, 0.f };

int create_camera(struct scene_obj *world, int obj_c, struct camera *cam, float vfov, int img_width, int img_height) {
        int c_i = 0;

        for (; c_i < obj_c; ++c_i) {
                if (CMRA == world[c_i].mat) {
                        break;
                }
        }

        if (c_i >= obj_c) {
                log_err("No camera in scene.");
                return FALSE;
        }

        float *view_dir = malloc(3 * sizeof(float));
        
        /* 
         * This syntax is ridiculously janky but I spent ages getting this to
         * to work and it seems that it very much has to be exactly like this.
         * The issue is in the disparity between `(float (*)[3])` and
         * `(float **)`. This syntax is used when each attribute of the camera
         * is set, so get used to it.
         */
        float *campos_ptr = &cam->pos[0];
        vecset(&campos_ptr, world[c_i].coords);

        vecset(&view_dir, add(world[c_i].dims, scale(cam->pos, -1)));

        if (!normalise(&view_dir)) {
                log_err("Invalid viewing direction.");
                return FALSE;
        }

        if (vfov <= 0.f) {
                log_err("Invalid field of view.");
                return FALSE;
        }

        float focus_dist = magnitude(add(world[0].coords, scale(cam->pos, -1)));

        float plane_h = 2.f * focus_dist * tan(deg_to_rad(vfov) / 2.f);
        float plane_w = plane_h * ((float)img_width / (float)img_height);

        float *plane_i = malloc(3 * sizeof(float));
        vecset(&plane_i, cross(view_dir, vup));
        if (!normalise(&plane_i)) {
                log_err("Invalid vector given.");
                return FALSE;
        }
        float *camdx_ptr = &cam->plane_dx[0];
        vecset(&camdx_ptr, scale(scale(plane_i, plane_w), 1.f / img_width));

        float *plane_j = malloc(3 * sizeof(float));
        vecset(&plane_j, cross(view_dir, plane_i));
        if (!normalise(&plane_j)) {
                log_err("Invalid vector given.");
                return FALSE;
        }
        float *camdy_ptr = &cam->plane_dy[0];
        vecset(&camdy_ptr, scale(scale(plane_j, plane_h), 1.f / img_height));

        float *plane_cnt = add(cam->pos, scale(view_dir, focus_dist));
        
        float *cam00_ptr = &cam->plane_00[0];
        vecset(&cam00_ptr, add(plane_cnt, add(scale(plane_i, -0.5f * plane_w), scale(plane_j, -0.5f * plane_h))));

        free(plane_cnt);
        plane_cnt = NULL;
        free(view_dir);
        view_dir = NULL;
        free(plane_i);
        plane_i = NULL;
        free(plane_j);
        plane_j = NULL;

        return TRUE;
}

float deg_to_rad(float angle) {
        return angle * PI / 180.f;
}

float magnitude(float *vec) {
        float m = sqrt(
                vec[0] * vec[0] + 
                vec[1] * vec[1] + 
                vec[2] * vec[2]
        );

        return m;
}

int normalise(float **vec) {
        float m = magnitude(*vec);

        if (0 == m) {
                return FALSE;
        }

        for (int i = 0; i < 3; ++i) {
                (*vec)[i] /= m;
        }

        return TRUE;
}

float *scale(float *vec, float scl) {
        float *res = calloc(3, sizeof(float));

        for (int i = 0; i < 3; ++i) {
                res[i] = vec[i] * scl;
        }

        return res;
}

float *add(float *vec1, float *vec2) {
        float *res = calloc(3, sizeof(float));

        for (int i = 0; i < 3; ++i) {
                res[i] = vec1[i] + vec2[i];
        }

        return res;
}

float *cross(float *vec1, float *vec2) {
        float *res = malloc(3 * sizeof(float));

        res[0] = (vec1[1] * vec2[2]) - (vec1[2] * vec2[1]);
        res[1] = (vec1[2] * vec2[0]) - (vec1[0] * vec2[2]);
        res[2] = (vec1[0] * vec2[1]) - (vec1[1] * vec2[0]);

        return res;
}

void vecset(float **vec1, float *vec2) {
        for (int i = 0; i < 3; ++i) {
                (*vec1)[i] = vec2[i];
        }
}