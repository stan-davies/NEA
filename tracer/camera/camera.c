#include "camera.h"

float vup[3] = { 0.f, 1.f, 0.f };

int create_camera(struct scene_obj *world, int obj_c, struct camera *cam, float focal_length, int img_width, int img_height) {
        int c_i;

        for (; c_i < obj_c; ++c_i) {
                if (CMRA == world[c_i].type) {
                        break;
                }
        }

        if (c_i >= obj_c) {
                log_err("No camera in scene.");
                return FALSE;
        }

        float *view_dir = malloc(3 * sizeof(float));

        for (int i = 0; i < 3; ++i) {
                cam->pos[i] = world[c_i].coords[i];
                view_dir[i] = world[c_i].dims[i] - cam->pos[i];
        }

        if (!unit(&view_dir)) {
                log_err("Invalid viewing direction.");
                return FALSE;
        }


        float vfov = deg_to_rad(1.f / focal_length);

        float *plane_cnt;

        plane_cnt = add(cam->pos, scale(view_dir, focal_length));

        float plane_h = 2.f * focal_length * tan(vfov);
        float plane_w = plane_h * ((float)img_width / (float)img_height);

        float *plane_i = malloc(3 * sizeof(float));
        vecset(plane_i, cross(view_dir, vup));
        if (!unit(plane_i)) {
                log_err("Invalid vector given.");
                return FALSE;
        }
        vecset(&(cam->plane_dx), scale(scale(plane_i, plane_w), 1.f / img_width));

        float *plane_j = malloc(3 * sizeof(float));
        vecset(plane_j, cross(view_dir, plane_i));
        if (!unit(plane_j)) {
                log_err("Invalid vector given.");
                return FALSE;
        }
        vecset(&(cam->plane_dy), scale(scale(plane_j, plane_h), 1.f / img_height));

        // currently does to the very top left of the viewing plane, not to the pixel centre
        vecset(&(cam->plane_00), add(plane_cnt, add(scale(plane_i, -0.5f), scale(plane_j, -0.5f))));

        return TRUE;
}

float deg_to_rad(int angle) {
        return (float)angle * PI / 180.f;
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

float *scale(float *vec, float scl) {
        for (int i = 0; i < 3; ++i) {
                vec[i] *= scl;
        }

        return vec;
}

float *add(float *vec1, float *vec2) {
        for (int i = 0; i < 3; ++i) {
                vec1[i] += vec2[i];
        }

        return vec1;
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