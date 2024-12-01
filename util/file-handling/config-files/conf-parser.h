#ifndef CONF_PARSER_H
#define CONF_PARSER_H

#include "conf-struct.h"

/*
 *   INPUT  : Path of configuration file. Pointer to array of configuration
 *            variables.
 *   OUTPUT : Success in parsing configuration file.
 * 
 *   DESC   : Creates an array of configuration variables where each is blank.
 */
int construct_config(char *path, struct config_var **config);

#endif