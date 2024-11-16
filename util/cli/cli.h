#ifndef CLI_H
#define CLI_H

#include <stdlib.h>
#include <string.h>

#include "glob.h"

/*
 *   INPUT  : `argc` and `argv` as given to `main` when program is run
 *   OUTPUT : command that has been chosen, or `NONE` for any errors
 * 
 *   DESC   : takes an input command and acts on each part of it
 */
enum PROGS take_input(int argc, char **argv);

/*
 *   INPUT  : choice of command as inputted by user
 *   OUTPUT : command code, or `NONE` for anything unexpected
 * 
 *   DESC   : converts command word to command code and validates it
 */
enum PROGS check_cmd(char **cmd_str);

int check_args();


// maximum length of string that describes each command
// includes room for `\0`
#define MAX_CMD_STR_LEN 8

/*
 *   INPUT  : command to get string for, pointer to string
 *   OUTPUT : whether or not the command given is valid
 * 
 *   DESC   : converts a command code to a string describing it
 */
int cmd_to_str(enum PROGS cmd, char **str);

#endif