#include "img-writer.h"

void write_texture(char *output_path, int texture_width, int texture_height, unsigned char *pixels) {
        FILE *out_f;

        out_f = fopen(output_path, "w");
        fprintf(out_f, "P3\n%d %d\n255\n", texture_width, texture_height);

        int pixel_i = 0;
        for (int y = 0; y < texture_height; ++y) {
                for (int x = 0; x < texture_width; ++x) {
                        fprintf(out_f, "%u %u %u\n", 
                        (unsigned int)pixels[pixel_i], 
                        (unsigned int)pixels[pixel_i + 1], 
                        (unsigned int)pixels[pixel_i + 2]);

                        pixel_i += 3;
                }
        }

        free(pixels);
}