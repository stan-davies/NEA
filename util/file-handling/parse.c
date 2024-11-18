#include "parse.h"

int parse(char *path, char **content, int *content_length) {
        FILE *file = fopen(path, "r");
        if (!file) {
                log_err("could not open shader file at '%s'", path);
                return FALSE;
        }

        char *cnt;
        size_t cnt_len = fread(cnt, 1, MAX_SHADER_LENGTH - 1, file);
        if ((int)cnt_len >= MAX_SHADER_LENGTH - 1) {
                log_err("shader file at '%s' is too long");
                return FALSE;
        }

        if (ferror(file)) {
                log_err("error reading file at '%s'", path);
                return FALSE;
        }

        cnt[cnt_len] = 0;
        fclose(file);

        content = cnt;
        content_length = &cnt_len;
        return TRUE;
}