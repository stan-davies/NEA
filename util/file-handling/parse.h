#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include "file-handling/log-writer/log-writer.h"

// 2^18 = 262144
#define MAX_SHADER_LENGTH 262144

/*
 *   INPUT  : Path to file. Pointer to string for file content. Length of file
 *            content.
 *   OUTPUT : Success in parsing shader file.
 * 
 *   DESC   : Parses content of file and adds `\0` to it.
 */
int parse(char *path, char **content, int *content_length);

#endif