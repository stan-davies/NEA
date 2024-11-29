#include "core.h"

int render() {
        enum STAGE current = BEGIN;

        // to config
        if (!advance(&current)) {
                log_err("could not advance");
        }
        // to scene
        if (!advance(&current)) {
                log_err("could not advance");
        }

        // to init
        if (!advance(&current)) {
                log_err("could not advance");
        }

        int program_id;

        if (!create_comp_program(&program_id)) {
                log_err("could not create compute program");
                return FALSE;
        }

        int img_width = 8;  // = from config file or default...
        int img_height = 8;

        int texture_id;

        create_texture(&texture_id, img_width, img_height);

        // to compute
        if (!advance(&current)) {
                log_err("could not advance");
        }

        run_comp_program(program_id, img_width, img_height);

        // to store
        if (!advance(&current)) {
                log_err("could not advance");
        }

        float *pixels;
        retrieve_texture(img_width, img_height, &pixels);

        char *output_path = "image.ppm"; // = from args
        write_texture(output_path, img_width, img_height, pixels);

        free(pixels);

        // to complete
        if (!advance(&current)) {
                log_err("could not advance");
        }

        return TRUE;
}