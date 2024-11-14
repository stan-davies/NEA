#ifndef SHAD_PARSER_H
#define SHAD_PARSER_H

int parse(char *path, char *content);

int compile(int *shader, TYPE type);

int create_shader(int *shader, char *path, TYPE type);

#endif