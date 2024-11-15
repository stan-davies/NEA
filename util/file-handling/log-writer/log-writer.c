#include "log-writer.h"

int init_log() {
        FILE *file = fopen(LOG_FILE_PATH, "w");
        if (!file) {
                printf("ERROR: could not begin log file\n");
                return FALSE;
        }

        fprintf(file, "beginning program with:\n\ttracer version %s\n", VERSION);
        
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

        fprintf(stderr, "ERROR: ");
        fprintf(stderr, format, argptr);
        fprintf(stderr, "\n");

        va_end(argptr);

        fclose(file);
        return TRUE;
}