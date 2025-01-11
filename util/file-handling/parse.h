#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include "file-handling/log-writer/log-writer.h"

// 2^18 = 262144
#define MAX_FILE_LENGTH     262144
// 2^5 = 32
#define MAX_LINE_LENGTH     32
// 2^4 = 16 
#define MAX_FILENAME_LENGTH 16
// 2^7
#define MAX_PATH_LENGTH     128

/*
 *   INPUT  : Path to file. Pointer to string for file content. Length of file
 *            content.
 *   OUTPUT : Success in parsing shader file.
 * 
 *   DESC   : Parses content of file and adds `\0` to it.
 */
int parse(char *path, char **content, int *content_length);

/*
 *   INPUT  : Pointer to string to be split. Pointer to split element. Pointer
 *            to length of split element. Delimiter to split on (anything other
 *            than a space or null character). Max length of split element.
 *   OUTPUT : Whether or not more splits remain in `*content`.
 * 
 *   DESC   : Splits `*content` on `delimiter`, putting the first split into
 *            `str`. As this function yields elements through sequential calls,
 *            it isn't actually splitting the whole thing. Rather, it builds
 *            the string out of `*content`, simultaneouslty incrementing
 *            `**content` through the string, `*content`.
 *   NOTE   : The pointer to the string to be split should not be the main
 *            pointer used for this string, as it is incremented. Keeping the
 *            original intact is important to ensure that it can be safely
 *            freed late. There is no greater virtue than considerate memory
 *            management.
 */
int yield_split(char **content, char **str, int *str_len, char delimiter, int max);

/*
 *   INPUT  : Pointer to string to clear. Length of string to clear.
 *   OUTPUT : -
 * 
 *   DESC   : Clears the given string by putting a null character in every
 *            place.
 */
void clear_str(char **str, int len);

#endif