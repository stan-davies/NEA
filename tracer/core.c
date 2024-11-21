#include "core.h"

int render() {
        int program_id;

        if (!create_comp_program(&program_id)) {
                log_err("could not create compute program");
                return FALSE;
        }

        // the config stuff probably wants to go here?

        int img_width;  // = from config file or default...
        int img_height;

        int texture_id;

        create_texture(&texture_id, img_width, img_height);

        run_comp_program(program_id, img_width, img_height);

        render_texture(texture_id);

        char *output_path; // = from args
        retrieve_texture(output_path, img_width, img_height);

        return TRUE;
}