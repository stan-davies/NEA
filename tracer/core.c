#include "core.h"

int render(float focal_length, int img_width, int img_height) {
        enum STAGE current = BEGIN;

        // to scene
        if (!advance(&current)) {
                log_err("Could not advance.");
                return FALSE;
        }

        struct scene_obj *world = calloc(MAX_OBJ_COUNT, sizeof(struct scene_obj));
        int obj_c;
        // make the file location customisable
        if (!create_world(".world", &world, &obj_c)) {
                log_err("Could not create world from scene file.");
                return FALSE;
        }
        log_world(world, obj_c);

        // to init
        if (!advance(&current)) {
                log_err("Could not advance.");
                return FALSE;
        }

        int program_id;

        if (!create_comp_program(&program_id)) {
                log_err("Could not create compute program.");
                return FALSE;
        }
        log("\tCreated compute program.");

        int texture_id;

        create_texture(&texture_id, img_width, img_height);
        log("\tCreated texture.");

        struct camera cam;
        if (!create_camera(world, obj_c, &cam, focal_length, img_width, img_height)) {
                log_err("Could not create camera.");
                return FALSE;
        }
        log("\tCreated camera.");

        // also check that these functions actually work
        // check it doesn't mess everything up by removing the camera from world
        set_world(program_id, world, obj_c);
        if (!log_gl_errs()) {
                log_err("OpenGL error detected.");
                return FALSE;
        }
        log("\tSet world.");
        set_camera(program_id, cam);

        if (!log_gl_errs()) {
                log_err("OpenGL error detected.");
                return FALSE;
        }

        // to compute
        if (!advance(&current)) {
                log_err("Could not advance.");
                return FALSE;
        }

        run_comp_program(program_id, img_width, img_height);

        // to store
        if (!advance(&current)) {
                log_err("Could not advance.");
                return FALSE;
        }

        float *pixels;
        retrieve_texture(img_width, img_height, &pixels);

        char *output_path = "image.ppm"; // = from args
        write_texture(output_path, img_width, img_height, pixels);

        free(pixels);

        // to complete
        if (!advance(&current)) {
                log_err("Could not advance.");
                return FALSE;
        }

        return TRUE;
}