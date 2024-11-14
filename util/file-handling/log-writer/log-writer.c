#include "log-writer.h"

int init_log() {
        FILE *file = fopen(LOG_FILE_PATH, "w");
        if (!file) {
                printf("ERROR: could not begin log file\n");
                return FALSE;
        }

        const GLubyte *gl_version = glGetString(GL_VERSION);
        const GLubyte *gl_vendor = glGetString(GL_VENDOR);
        const GLubyte *glsl_version = glGetString(GL_SHADING_LANGUAGE_VERSION);
        // log ALL that

        fprintf(file, "beginning program with:\n tracer version %s\n opengl version %s\n opengl implementation vendor %s\n glsl version %s\n----------", VERSION, gl_version, gl_vendor, glsl_version);
        
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
        fprintf(file, format, argptr);
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
        fprintf(file, "ERROR: %s", format, argptr);

        printf("ERROR: %s", format, argptr);

        va_end(argptr);

        fclose(file);
        return TRUE;
}