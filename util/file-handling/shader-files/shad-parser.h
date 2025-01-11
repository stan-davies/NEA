#ifndef SHAD_PARSER_H
#define SHAD_PARSER_H

#include <stdio.h>
#include <stdlib.h>

#include "opengl/OpenGL.h"
#include "file-handling/parse.h"

/*
 *   INPUT  : Path to directory containing glsl files. Pointer to a string to
 *            fill with glsl code from files.
 *   OUTPUT : Success in preprocessing.
 *
 *   DESC   : Deals with `#include` statements in a group of glsl files.
 */
int preprocess(char *dir_path, char **shader_string);

/*
 *   INPUT  : Path to directory containing glsl files. Name of file. Pointer
 *            to string for content of file. Pointer to int for length of file.
 *   OUTPUT : Success in parsing.
 *
 *   DESC   : Finds `{name}.glsl` file and parses it.
 */
int get_file_cnt(char *dir_path, char *name, char **cnt, int *cnt_len);

/*
 *   INPUT  : Path to directory containing glsl files. Pointer to string for 
 *            content of file. Length of file.
 *   OUTPUT : Success in fulfilling directives.
 *
 *   DESC   : Searches shader file for '#include' directives and inserts 
 *            specified code.
 */
int direct(char *dir_path, char **content, int content_len);

/*
 *   INPUT  : Pointer to GL id of shader. Path to directory containing shader
 *            files. GL type of shader.
 *   OUTPUT : Success in parsing, preprocessing, and creating shader.
 *
 *   DESC   : Parses and preprocesses shader code, creates GL shader, compiles
 *            code, and validate the shader.
 */
int create_shader(int *shader_id, char *dir_path, GLenum type);

#endif