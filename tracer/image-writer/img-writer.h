#ifndef IMG_WRITER_H
#define IMG_WRITER_H

#include <stdio.h>

/*
 *   INPUT  : Path to image file where data should be written. Width of
 *            texture. Height of texture. Pixel data to write.
 *   OUTPUT : -
 * 
 *   DESC   : Writes pixel data to image file in PPM `P3` format.
 */
void write_texture(char *output_path, int texture_width, int texture_height, unsigned char *pixels);

#endif