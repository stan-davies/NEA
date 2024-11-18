#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include "file-handling/log-writer/log-writer.h"

// 2^18 = 262144
#define MAX_SHADER_LENGTH 262144

/*
 *   INPUT  : path to file, pointer to string for file content
 *   OUTPUT : success in parsing shader file
 * 
 *   DESC   : parses content of file and adds `\0` to it
 */
int parse(char *path, char **content, int *content_length);

#endif