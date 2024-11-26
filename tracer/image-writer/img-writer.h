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
void write_texture(char *output_path, int texture_width, int texture_height, float *pixels);

/*
 *   INPUT  : Number to convert.
 *   OUTPUT : Converted number.
 * 
 *   DESC   : Converts a number from [0.0, 1.0] to [0, 255]. This is used as
 *            OpenGL plays much nicer when 32-bit floats are used to represent
 *            pixels, as opposed to some integer format, such as unsigned
 *            bytes, which I foolishly tried to use before. As I am here, I
 *            feel like adding that it also gets nasty if you try to ignore the
 *            alpha channel. I am ignoring it, as it isn't getting written to
 *            the file, but it must be kept in memory anyway.
 *            No validation is done to ensure that the given number is actually
 *            in the range [0.0, 1.0], and as such there is no guarentee that
 *            output is in the range [0, 255]. This is because I have done this
 *            as an inline function for efficiency, so the task of ensuring
 *            correctness is left to the user of the function. Sure, the user
 *            of the function will only ever be me, but I still think that this
 *            is the ideal way to implement this.
 */
inline int channel_rep_convert(float n);

#endif