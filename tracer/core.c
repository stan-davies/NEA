#include "core.h"

int render() {
        int program_id;

        if (!create_comp_program(&program_id)) {
                log_err("could not create compute program");
                return FALSE;
        }

        // the config stuff probably wants to go here?

        int img_width = 4;  // = from config file or default...
        int img_height = 4;

        int texture_id;

        create_texture(&texture_id, img_width, img_height);

        run_comp_program(program_id, img_width, img_height);

        float *pixels;
        retrieve_texture(img_width, img_height, &pixels);

        char *output_path = "image.ppm"; // = from args
        write_texture(output_path, img_width, img_height, pixels);

        free(pixels);

        return TRUE;
}