#include "img-writer.h"

void write_texture(char *output_path, int texture_width, int texture_height, float *pixels) {
        FILE *out_f;

        out_f = fopen(output_path, "w");
        if (!out_f)  {
                log_err("Could not open file '%s'.", output_path);
                return;
        }
        fprintf(out_f, "P3\n%d %d\n255\n", texture_width, texture_height);
        
        int pixel_i = 0;
        for (int y = 0; y < texture_height; ++y) {
                for (int x = 0; x < texture_width; ++x) {
                        fprintf(out_f, "%d %d %d\n", 
                        channel_rep_convert(pixels[pixel_i]), 
                        channel_rep_convert(pixels[pixel_i + 1]), 
                        channel_rep_convert(pixels[pixel_i + 2]));

                        // ignore alpha channel
                        pixel_i += 4;
                }
        }
}

int channel_rep_convert(float n) {
        return (int)(n * 255.f);
}