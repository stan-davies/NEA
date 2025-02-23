#ifndef DISPOSE_H
#define DISPOSE_H

#include "tracer/rend_const.h"
#include "tracer/core.h"
#include "cli/cli.h"

/*
 *   INPUT  : `argc` and `argv` as given to `main` when program is run.
 *   OUTPUT : Success in running renderer.
 * 
 *   DESC   : Gets any given configuration options and then disposes the
 *            renderer using these options. If any option is left un-set, then
 *            a default value, as defined in `tracer/core.h` is used.
 */
int dispose_renderer(int argc, char **argv);

#endif