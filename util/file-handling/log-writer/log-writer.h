#ifndef LOG_WRITER_H
#define LOG_WRITER_H

#include "opengl/OpenGL.h"

#include <stdio.h>
#include <stdarg.h>

#include "global.h"
#include "cli/cli.h"
#include "file-handling/scene-files/scen-struct.h"


#define LOG_FILE_PATH ".log"

/* 
 * Maximum length of shader / program logs, as used in `log_shader_logs` and
 * `log_program_logs`.
 */
#define MAX_GL_LOGS_LEN 2048
#define MAX_PARAM_NAME  16

/*
 *   INPUT  : -
 *   OUTPUT : Success in creating file.
 *
 *   DESC   : Resets the log file.
 */
int init_log();

/*
 *   INPUT  : Command code that program is starting with.
 *   OUTPUT : Success in logging key data.
 * 
 *   DESC   : Creates first line in log file, which indicates that the program
 *            is starting, what it is going to do (render or edit scenefile) 
 *            and which version of the program is being used.
 */
int log_vars(enum PROGS cmd);

/*
 *   INPUT  : Format for message to log. Arguments to place into format.
 *   OUTPUT : Success in logging message.
 *
 *   DESC   : Writes the given message to the log file. `\n` will be 
 *            automatically appended to the end of string.
 */
int log(char *format, ...);

/*
 *   INPUT  : Format for error to log. Arguments to place into format.
 *   OUTPUT : Success in logging error.
 *
 *   DESC   : Writes the given error to the log file. 'ERROR:' is prepended to
 *            the error and `\n` will be automatically appended to the string.
 */
int log_err(char *format, ...);

/*
 *   INPUT  : GL ID of shader to log info for.
 *   OUTPUT : Success in logging logs.
 * 
 *   DESC   : Logs data taken from OpenGL about the given shader. This includes
 *            information about errors and other, less significant, stuff.
 */
int log_shader_logs(int shader_id);

/*
 *   INPUT  : GL ID of program to log info for.
 *   OUTPUT : Success in logging logs.
 *
 *   DESC   : Logs data taken from OpenGL about the given program. This
 *            includes information about errors and other, less significant,
 *            stuff.
 */
int log_program_logs(int program_id);

/*   
 *   INPUT  : -
 *   OUTPUT : Success in logging errors.
 * 
 *   DESC   : Logs codes of any errors on the OpenGL error queue. To find what
 *            a given code means, go google the OpenGL documentation. To find
 *            what caused the error, run this function before and after what you
 *            reckon caused it and then just keep having a look.
 */
int log_gl_errs();

/*
 *   INPUT  : World (array of objects). Number of objects in world.
 *   OUTPUT : -
 * 
 *   DESC   : Logs all of the data for every object in the world.
 */
void log_world(struct scene_obj *world, int obj_c);

#endif