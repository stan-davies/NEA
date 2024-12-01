#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include "file-handling/log-writer/log-writer.h"

// 2^18 = 262144 (still sort of an arbitrary choice)
#define MAX_FILE_LENGTH     262144
// 2^5 = 32 (still sort of an arbitrary choice)
#define MAX_LINE_LENGTH     32
// pretty arbitrary 
#define MAX_FILENAME_LENGTH 15
// also pretty arbitrary
#define MAX_PATH_LENGTH     50

/* 
 * Character codes for use in various different functions across various
 * different functions and files. It may seem an odd choice to put them all 
 * here if their use is distributed. My reasoning was that this file should
 * be treated like a central base for all things file related. Hence the
 * above definitions of `MAX_FILE_LENGTH` and so on. Therefore, centralising
 * these definitions felt like the most logical course of action.
 */
#define LF_C  10
#define NL_C  0
#define SP_C  32
#define SL_C  47
#define CM_C  44
#define CHR_9 57
#define HSH_C 35
#define QUT_C 34
#define I_C   105

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
 *            to length of split element. Delimiter to split on. Max length of
 *            split element.
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

#endif