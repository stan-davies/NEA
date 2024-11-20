#ifndef CLI_H
#define CLI_H

#include <stdlib.h>
#include <string.h>

#include "global.h"

/*
 *   INPUT  : `argc` and `argv` as given to `main` when program is run.
 *   OUTPUT : Command that has been chosen, or `NONE` for any errors.
 * 
 *   DESC   : Takes an input command and acts on each part of it.
 */
enum PROGS take_input(int argc, char **argv);

/*
 *   INPUT  : Choice of command as given in main args.
 *   OUTPUT : Command code, or `NONE` for anything unexpected.
 * 
 *   DESC   : Converts command word to command code and validates it.
 */
enum PROGS check_cmd(char **cmd_str);

// does nothing yet but it will...
int check_args();


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