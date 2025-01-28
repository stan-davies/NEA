#ifndef CLI_H
#define CLI_H

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "global.h"
#include "file-handling/log-writer/log-writer.h"
#include "file-handling/parse.h"

/*
 *   INPUT  : `argc` and `argv` as given to `main` when program is run.
 *   OUTPUT : Command that has been chosen, or `NONE` for any errors.
 * 
 *   DESC   : Takes an input command and determines which major command has
 *            given.
 */
enum PROGS take_input(int argc, char **argv);

enum TYPES {
        INT,
        FLT
};

/*
 *   INPUT  : `argc` and `argv` as given to `main` when program is run. Pointer
 *            to float for a given vertical fov. Pointer to an integer for a
 *            given image width. Pointer to an integer for a given image 
 *            height. Pointer to string for output file path. Pointer to string
 *            for scene file path.
 *   OUTPUT : Whether or not *all* options were valid.
 * 
 *   DESC   : Goes through each option given in `argv` and gets any relevant
 *            data from it. These data will be placed into the function
 *            arguments.
 */
int read_args_rend(int argc, char **argv, float *vfov, int *width, int *height, char **output_f, char **scene_file);

/*
 *   INPUT  : String containing argument to check. What data type the argument
 *            should be.
 *   OUTPUT : If the argument is valid, and can therefore be safely converted.
 * 
 *   DESC   : Ensures the given argument contains only digits, and potentially
 *            a single decimal separator if it is a floating point number.
 */
int valid_arg(char *arg, enum TYPES type);

/*
 *   INPUT  : String containing file path to check.
 *   OUTPUT : If the filepath is valid.
 * 
 *   DESC   : Checks the validity of the given file path. A valid path may
 *            contain letters, '.', '-' and '_'.
 */
int valid_fp(char *fp);

/*
 *   INPUT  : Choice of command as given in main args.
 *   OUTPUT : Command code, or `NONE` for anything unexpected.
 * 
 *   DESC   : Converts command word to command code and validates it.
 */
enum PROGS check_cmd(char **cmd_str);

/* 
 * Maximum length of string that describes each command. Includes room for 
 * `\0`.
 */
#define MAX_CMD_STR_LEN 8

/*
 *   INPUT  : Command to get string for. Pointer to string.
 *   OUTPUT : Whether or not the command given is valid.
 * 
 *   DESC   : Converts a command code to a string describing it.
 */
int cmd_to_str(enum PROGS cmd, char **str);

#endif