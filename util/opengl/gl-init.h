#ifndef GL_INIT_H
#define GL_INIT_H

#include "OpenGL.h"
#include "global.h"

#include "file-handling/log-writer/log-writer.h"

/*
 *   INPUT  : which type of pprogram is being run, pointer to where the window should be created
 *   OUTPUT : whether or not initialisation of OpenGL was successful
 *   
 *   DESC   : initialises OpenGL with a hidden window
 */
int init_gl(enum PROGS type, GLFWwindow *window);

/*
 *   INPUT  : -
 *   OUTPUT : -
 * 
 *   DESC   : terminates OpenGL
 */
void term_gl();

/*
 *   INPUT  : GLFW error code, GLFW description of error
 *   OUTPUT : -
 *
 *   DESC   : callback for GLFW to call when an error occurs, data is used to log the error
 */
void glfw_error_callback(int error, const char *description);

/*
 *   INPUT  : -
 *   OUTPUT : -
 * 
 *   DESC   : logs some key opengl variables concerning versions
 */
void log_gl_vars();

#endif