#ifndef LOG_WRITER_H
#define LOG_WRITER_H

#include "opengl/OpenGL.h"

#include <stdio.h>
#include <stdarg.h>

#include "global.h"
#include "cli/cli.h"


#define LOG_FILE_PATH ".log"

/*
 *   INPUT  : -
 *   OUTPUT : success in creating file
 *
 *   DESC   : resets the log file
 */
int init_log();

/*
 *   INPUT  : command code that program is starting with
 *   OUTPUT : sucess in logging key data
 * 
 *   DESC   : creates first line in log file, which indicates that the
 *            program is starting, what it is going to do (render or 
 *            edit scenefile) and which version of the program is being
 *            used
 */
// creates a fresh log file and writes the current version and command to it
int log_vars(enum PROGS cmd);

/*
 *   INPUT  : format for message to log, arguments to place into format
 *   OUTPUT : success in logging message
 *
 *   DESC   : writes the given message to the log file
 *            `\n` will be automatically appended to the end of string
 */
int log(char *format, ...);

/*
 *   INPUT  : format for error to log, arguments to place into format
 *   OUTPUT : success in logging error
 *
 *   DESC   : writes the given error to the log file and outputs it to the console
 *            'ERROR:' is prepended to the front of the error
 *            `\n` will be automatically appended to the end of string
 */
int log_err(char *format, ...);

#endif