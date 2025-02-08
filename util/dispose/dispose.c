#include "dispose.h"

int dispose_renderer(int argc, char **argv) {
        float vfov = 0;
        int image_width = 0;
        int image_height = 0;
        int max_samples = 0;
        int max_bounces = 0;
        char *output_file = calloc(MAX_FILENAME_LENGTH, sizeof(char));
        char *scene_file = calloc(MAX_FILENAME_LENGTH, sizeof(char));

        if (!read_args_rend(argc, argv, &vfov, &image_width, &image_height, &max_bounces, &max_samples, &output_file, &scene_file)) {
                log_err("Unable to read arguments for rendering mode.");
                return FALSE;
        }

        if (0 == vfov) {
                vfov = DEF_VFOV;
                log("No vfov given, default value of %.2f will be used.", vfov);
        }

        if (0 == image_width) {
                image_width = DEF_IMG_WIDTH;
                log("No image width given, default value of %d will be used.", image_width);
        }

        if (0 == image_height) {
                image_height = DEF_IMG_HEIGHT;
                log("No image height given, default value of %d will be used.", image_height);
        }

        if (0 == max_samples) {
                max_samples = DEF_MAX_SAMPLES;
                log("No max samples given, default value of %d will be used.", max_samples);
        }

        if (0 == max_bounces) {
                max_bounces = DEF_MAX_BOUNCES;
                log("No max bounces given, default value of %d will be used.", max_bounces);
        }

        if (NL_C == output_file[0]) {
                sprintf(output_file, DEF_OF);
                log("No output file path given, default value of \"%s\" will be used.", DEF_OF);
        }

        if (NL_C == scene_file[0]) {
                sprintf(scene_file, DEF_SF);
                log("No scene_file path given, default value of \"%s\" will be used.", DEF_SF);
        }

        return render(vfov, image_width, image_height, max_samples, max_bounces, output_file, scene_file);
}