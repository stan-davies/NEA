/* GLOBALS:
 * 
 * These are globals used as so across the entire program. They
 * are not specific to any one part of it, and so are put in this
 * file which is included in almost every other file.
 * 
 */

#ifndef GLOB_H
#define GLOB_H

#include "version.h"

/* Hopefully, these three macros are fairly self-explanatory.

 * If not: C does not define true, false, and null by default.
 * They do exist in some of the standard library packages
 * but it can be good to make them yourself so you are certain 
 * that they are right.
 
 * A C macro is a piece of code that is referred to by a name.
 * For example, the name `TRUE` refers to the code `1`. The
 * first stage of C compilation is preprocesing. Part of this
 * stage is to replace all references to macros with the code
 * that those macros describe. So in this case, all references
 * to `TRUE` wil be replaced with the code `1`. Therefore, when
 * the code is then compiled, everything works!

 */
#define TRUE  1
#define FALSE 0
#define NULL (void *)(0)

/* These differentiate between sides of the program. There are
 * numerous places in which functionality differs depending on
 * whether we are currently rendering a scene or editing a file,
 * and so tis allows for that.
 */
enum PROGS {
        REND,
        EDIT,
        NONE
};

#endif