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
        char *shader_log = calloc(MAX_GL_LOGS_LEN, sizeof(char));
        glGetShaderInfoLog(shader_id, MAX_GL_LOGS_LEN, &actual_len, shader_log);
        return log("shader logs for '%d':\n%s", shader_id, shader_log);
}

int log_program_logs(int program_id) {
        int actual_len = 0;
        char *prog_log = calloc(MAX_GL_LOGS_LEN, sizeof(char));
        glGetProgramInfoLog(program_id, MAX_GL_LOGS_LEN, &actual_len, prog_log);
        return log("program info log for '%d':\n%s", program_id, prog_log);
}

int log_gl_errs() {
        register int err;
        int success;
        while ((err = glGetError()) != GL_NO_ERROR) {
                success = log_err("GL error code: 0x%.4x\n\"But what is...\" -> https://www.khronos.org/opengl/wiki/OpenGL_Error#Meaning_of_errors", err);
        }
        return success;
}