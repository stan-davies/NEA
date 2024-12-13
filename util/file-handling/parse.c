#include "parse.h"

int parse(char *path, char **content, int *content_length) {
        FILE *file = fopen(path, "r");
        if (!file) {
                log_err("could not open shader file at '%s'", path);
                return FALSE;
        }

        *content = calloc(MAX_FILE_LENGTH, sizeof(char));
        *content_length = fread(*content, sizeof(char), MAX_FILE_LENGTH - 1, file);

        (*content)[(*content_length)] = 0;
        fclose(file);
        return TRUE;
}

int yield_split(char **content, char **str, int *str_len, char delimiter, int max) {
        *str_len = 0;
        char curr = 0;

        for (;;) { // infinite loop that doesn't make the compiler mad (as `while (true)` does)
                curr = (*content)[0];
                if (SP_C == curr) {
                        (*content)++; // move the pointer through the string
                        continue;
                }
                if (delimiter == curr || NL_C == curr) {
                        (*content)++;
                        (*str)[*str_len] = NL_C; // cap with null
                        break;
                }
                if (*str_len >= max) {
                        break;
                }
                (*str)[*str_len] = curr;
                (*str_len)++;

                (*content)++;
        }

        if (0 == *str_len) {
                return FALSE;
        }

        return TRUE;
}