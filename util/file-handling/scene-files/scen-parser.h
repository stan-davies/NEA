#ifndef SCEN_PARSER_H
#define SCEN_PARSER_H

#include "file-handling/parse.h"
#include "scen-struct.h"

#define MAX_PARAM_LEN  8

enum ARG_TYPE {
        ARG_FLT,
        ARG_MAT,
        ARG_INV
};

/*
 *   INPUT  : Path to scene description file. Pointer to array of objects in
 *            world. Pointer to count of objects in scene.
 *   OUTPUT : Success in parsing scene file.
 * 
 *   DESC   : Converts scene file to an array of scene objects. First line
 *            should be objc.
 */
int create_world(char *path, struct scene_obj **world, int *object_count);

/*
 *   INPUT  : Pointer to integer to store type. First character of line being
 *            analysed.
 *   OUTPUT : Whether or not `line0` is valid.
 * 
 *   DESC   : Checks validity of `line0` and sets `type` to the correspodning
 *            value, or to 0 if the line is a comment or newline.
 */
int choose_type(int *type, char line0);

/*
 *   INPUT  : String containing current argument. Length of string.
 *   OUTPUT : Type of argument given.
 * 
 *   DESC   : Analyses argument to check that it is either a valid float or
 *            material descriptor. It will be declared invalid in all other
 *            cases.
 */
enum ARG_TYPE get_arg_type(char *arg, int len);

#endif