#include "dispose.h"

int dispose_renderer(int argc, char **argv) {
        float focal_length = 0;
        int image_width = 0;
        int image_height = 0;

        if (!read_args_rend(argc, argv, &focal_length, &image_width, &image_height)) {
                log_err("Unable to read arguments for rendering mode.");
                return FALSE;
        }

        if (0 == focal_length) {
                focal_length = DEF_FOCAL_LENGTH;
                log("No focal length given, default value of %.2f will be used.", focal_length);
        }

        if (0 == image_width) {
                image_width = DEF_IMG_WIDTH;
                log("No image width given, default value of %d will be used.", image_width);
        }

        if (0 == image_height) {
                image_height = DEF_IMG_HEIGHT;
                log("No image height given, default value of %d will be used.", image_height);
        }

        return render(focal_length, image_width, image_height);
}