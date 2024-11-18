#ifndef SHAD_PARSER_H
#define SHAD_PARSER_H

#include <stdio.h>
#include <stdlib.h>

#include "OpenGL.h"
#include "parse.h"

#define MAX_FILENAME_LEN 15

#define HASH_CHR 35
#define QUT_CHR  34

/*
 *   INPUT  : path to directory containing glsl files, pointer to a string to fill with glsl 
 *            code from files
 *   OUTPUT : success in preprocessing
 *
 *   DESC   : deals with '#include' statements in a group of glsl files
 */
int preprocess(char *dir_path, char **shader_string);

/*
 *   INPUT  : path to directory containing glsl files, name of file, pointer to string for 
 *            content of file, pointer to int for length of file
 *   OUTPUT : success in parsing
 *
 *   DESC   : finds {name}.glsl file and parses it
 */
int get_file_cnt(char *dir_path, char *name, char **cnt, int *cnt_len);

/*
 *   INPUT  : path to directory containing glsl files, pointer to string for content of file, 
 *            pointer to int for length of file
 *   OUTPUT : success in fulfilling directives
 *
 *   DESC   : searches shader file for '#include' directives and inserts specified code
 *   TODO   : ensure the same block of code is not inserted twice (read files array?)
 */
int direct(char *dir_path, char **content, int *content_len);

/*
 *   INPUT  : GL id of shader, path to directory containing shader files, GL type of shader
 *   OUTPUT : success in parsing, preprocessing, and creating shader
 *
 *   DESC   : parses and preprocesses shader code, creates GL shader, compiles code, and validate 
 *            the shader
 */
int create_shader(int *shader_id, char *dir_path, GLenum type);

#endif