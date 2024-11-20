#include "parse.h"

int parse(char *path, char **content, int *content_length) {
        FILE *file = fopen(path, "r");
        if (!file) {
                log_err("could not open shader file at '%s'", path);
                return FALSE;
        }

        *content = calloc(MAX_SHADER_LENGTH, sizeof(char));
        *content_length = fread(*content, sizeof(char), MAX_SHADER_LENGTH - 1, file);

        (*content)[(*content_length)] = 0;
        fclose(file);
        return TRUE;
}