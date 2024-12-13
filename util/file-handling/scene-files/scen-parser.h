#ifndef SCEN_PARSER_H
#define SCEN_PARSER_H

#include "file-handling/parse.h"
#include "scen-struct.h"

#define MAX_OBJ_COUNT  128
#define MAX_PARAM_LEN  8

/*
 *   INPUT  : Path to scene description file. Pointer to array of objects in
 *            world. Pointer to count of objects in scene.
 *   OUTPUT : Success in parsing scene file.
 * 
 *   DESC   : Converts scene file to an array of scene objects. First line
 *            should be objc.
 */
int create_world(char *path, struct scene_obj **world, int *object_count);

#endif