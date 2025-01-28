/* GLOBALS:

 * These are globals used as so across the entire program. They are not
 * specific to any one part of it, and so are put in this file which is 
 * included in almost every other file.
 */

#ifndef GLOB_H
#define GLOB_H

#include "version.h"

/* 
 * Hopefully, these three macros are fairly self-explanatory.
 *
 * If not: C does not define true, false, and null by default. They do exist in
 * some of the standard library packages but it can be good to make them
 * yourself so you are certain that they are right.
 *
 * A C macro is a piece of code that is referred to by a name. For example, the
 * name `TRUE` refers to the code `1`. The first stage of C compilation is 
 * preprocesing. Part of this stage is to replace all references to macros with
 * the code that those macros describe. So in this case, all references to
 * `TRUE` wil be replaced with the code `1`. Therefore, when the code is then 
 * compiled, everything works!
 */
#define TRUE  1
#define FALSE 0
#define NULL (void *)(0)

/* 
 * These differentiate between sides of the program. There are numerous places
 * in which functionality differs depending on whether we are currently 
 * rendering a scene or editing a file, and so tis allows for that.
 */
enum PROGS {
        REND,
        HELP,
        NONE
};

/* 
 * Character codes for use in various different functions across various
 * different files. These are used a lot in many of the `file-handling/`
 * functions, but also appear in `cli.c`.
 */
#define LF_C  10   // '\n'
#define NL_C  0    // '\0'
#define SP_C  32   // ' '
#define SL_C  47   // '/'
#define CM_C  44   // ','
#define PT_C  46   // '.'
#define HSH_C 35   // '#'
#define QUT_C 34   // '"'
#define UND_C 95   // '_'
#define DSH_C 45   // '-'
#define CHR_9 57   // '9'
#define CHR_0 48   // '0'
#define CHR_A 65   // 'A'
#define CHR_Z 90   // 'Z'
#define CHR_a 97   // 'a'
#define CHR_i 105  // 'i'
#define CHR_z 122  // 'z'

#endif