#include "core.h"

int render() {
        enum STAGE current = BEGIN;

        // to config
        advance(&current);
        // to scene
        advance(&current);

        // to init
        advance(&current);

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
        advance(&current);

        run_comp_program(program_id, img_width, img_height);

        // to store
        advance(&current);

        float *pixels;
        retrieve_texture(img_width, img_height, &pixels);

        char *output_path = "image.ppm"; // = from args
        write_texture(output_path, img_width, img_height, pixels);

        free(pixels);

        // to complete
        advance(&current);

        return TRUE;
}