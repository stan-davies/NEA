#include "log-writer.h"

int init_log() {
        FILE *file = fopen(LOG_FILE_PATH, "w");
        if (!file) {
                printf("ERROR: could not begin log file\n");
                return FALSE;
        }

        fprintf(file, "");
        
        fclose(file);
        return TRUE;
}

int log_vars(enum PROGS cmd) {
        FILE *file = fopen(LOG_FILE_PATH, "w");
        if (!file) {
                printf("ERROR: could not begin log file\n");
                return FALSE;
        }

        char *cmd_str;
        if (!cmd_to_str(cmd, &cmd_str)) {
                printf("ERROR: invalid command given");
                return FALSE;
        }

        fprintf(file, "beginning program in mode %s at %s with:\n", cmd_str, VERSION);

        fclose(file);
        return TRUE;
}

int log(char *format, ...) {
        FILE *file = fopen(LOG_FILE_PATH, "a");
        if (!file) {
                printf("ERROR: could not open log file\n");
                return FALSE;
        }

        va_list argptr;
        va_start(argptr, format);

        vfprintf(file, format, argptr);
        fprintf(file, "\n");

        va_end(argptr);

        fclose(file);
        return TRUE;
}

int log_err(char *format, ...) {
        FILE *file = fopen(LOG_FILE_PATH, "a");
        if (!file) {
                printf("ERROR: could not open log file\n");
                return FALSE;
        }

        va_list argptr;

        va_start(argptr, format);
        fprintf(file, "ERROR: ");
        vfprintf(file, format, argptr);
        fprintf(file, "\n");
        va_end(argptr);

        va_start(argptr, format);
        fprintf(stderr, "ERROR: ");
        vfprintf(stderr, format, argptr);
        fprintf(stderr, "\n");
        va_end(argptr);

        fclose(file);
        return TRUE;
}

int log_shader_logs(int shader_id) {
        int actual_len = 0;
        char *shader_log = calloc(MAX_SHADER_LOGS_LEN, sizeof(char));
        glGetShaderInfoLog(shader_id, MAX_SHADER_LOGS_LEN, &actual_len, shader_log);
        return log("shader logs for '%d': %s", shader_id, shader_log);
}