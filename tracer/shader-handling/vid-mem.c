#include "vid-mem.h"

void create_texture(int *texture_id, int texture_width, int texture_height) {
        glGenTextures(1, texture_id);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, *texture_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, texture_width, texture_height, 0, GL_RGBA, GL_FLOAT, NULL);

        glBindImageTexture(0, *texture_id, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
}

void set_world(int program_id, struct scene_obj world[MAX_OBJ_COUNT], int obj_c) {
        char *var_prefix = calloc(MAX_SHDR_VAR_LEN, sizeof(char));
        char *var = calloc(MAX_SHDR_VAR_LEN, sizeof(char));
        int index = 0;

        int light_found = FALSE;

        glUseProgram(program_id);
        for (int i = 0; i < obj_c; ++i) {
                if (CMRA == world[i].mat) {
                        continue;
                } else if (LGHT == world[i].mat) {
                        light_found = TRUE;
                }

                sprintf(var_prefix, "world[%d].", index);
                
                sprintf(var, "%s%s", var_prefix, "type");
                glUniform1i(glGetUniformLocation(program_id, var), world[i].type);

                sprintf(var, "%s%s", var_prefix, "coords");
                glUniform3fv(glGetUniformLocation(program_id, var), 1, world[i].coords);

                sprintf(var, "%s%s", var_prefix, "albedo");
                glUniform3fv(glGetUniformLocation(program_id, var), 1, world[i].albedo);

                sprintf(var, "%s%s", var_prefix, "dims");
                glUniform3fv(glGetUniformLocation(program_id, var), 1, world[i].dims);

                sprintf(var, "%s%s", var_prefix, "mat");
                glUniform1i(glGetUniformLocation(program_id, var), world[i].mat);

                ++index;
        }

        // 1 is subtracted to account for the removed camera
        glUniform1i(glGetUniformLocation(program_id, "obj_c"), obj_c - 1);
        glUniform1i(glGetUniformLocation(program_id, "do_light"), light_found);
}

void set_camera(int program_id, struct camera cam) {
        glUseProgram(program_id);
        /*
         * Hard coding in the variable names is less than ideal, but it is, in
         * this case, the price that must be paid.
         */
        glUniform3fv(glGetUniformLocation(program_id, "cam.pos"), 1, cam.pos);
        glUniform3fv(glGetUniformLocation(program_id, "cam.plane_00"), 1, cam.plane_00);
        glUniform3fv(glGetUniformLocation(program_id, "cam.plane_dx"), 1, cam.plane_dx);
        glUniform3fv(glGetUniformLocation(program_id, "cam.plane_dy"), 1, cam.plane_dy);
}

void set_params(int program_id, int max_bounces, int max_samples, float ambient_coef) {
        glUseProgram(program_id);

        glUniform1i(glGetUniformLocation(program_id, "max_bounces"), max_bounces);
        glUniform1i(glGetUniformLocation(program_id, "max_samples"), max_samples);
        glUniform1f(glGetUniformLocation(program_id, "ambient_coef"), ambient_coef);
}

void retrieve_texture(int img_width, int img_height, float **pixels) {
        *pixels = calloc(img_width * img_height, 4 * sizeof(float));
        glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_FLOAT, *pixels);
}