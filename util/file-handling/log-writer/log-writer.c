#include "log-writer.h"

int init_log() {
        FILE *file = fopen(LOG_FILE_PATH, "w");
        if (!file) {
                printf("ERROR: Could not begin log file.\n");
                return FALSE;
        }

        fprintf(file, "");
        
        fclose(file);
        return TRUE;
}

int log_vars(enum PROGS cmd) {
        FILE *file = fopen(LOG_FILE_PATH, "w");
        if (!file) {
                printf("ERROR: Could not begin log file.\n");
                return FALSE;
        }

        char *cmd_str;
        if (!cmd_to_str(cmd, &cmd_str)) {
                printf("ERROR: Invalid command given.");
                return FALSE;
        }

        fprintf(file, "Beginning program in mode %s at %s with:\n", cmd_str, VERSION);

        fclose(file);
        return TRUE;
}

int log(char *format, ...) {
        FILE *file = fopen(LOG_FILE_PATH, "a");
        if (!file) {
                printf("ERROR: Could not open log file.\n");
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
                printf("ERROR: Could not open log file.\n");
                return FALSE;
        }

        va_list argptr;

        va_start(argptr, format);
        fprintf(file, "ERROR: ");
        vfprintf(file, format, argptr);
        fprintf(file, "\n");
        va_end(argptr);

        fclose(file);
        return TRUE;
}

int log_shader_logs(int shader_id) {
        int actual_len = 0;
        char *shader_log = calloc(MAX_GL_LOGS_LEN, sizeof(char));
        glGetShaderInfoLog(shader_id, MAX_GL_LOGS_LEN, &actual_len, shader_log);
        return log("Shader logs for '%d':\n%s", shader_id, shader_log);
}

int log_program_logs(int program_id) {
        int actual_len = 0;
        char *prog_log = calloc(MAX_GL_LOGS_LEN, sizeof(char));
        glGetProgramInfoLog(program_id, MAX_GL_LOGS_LEN, &actual_len, prog_log);
        return log("Program info log for '%d':\n%s", program_id, prog_log);
}

int log_gl_errs() {
        register int err;
        int success;
        while ((err = glGetError()) != GL_NO_ERROR) {
                success = log_err("GL error code: 0x%.4x\n\"But what is...\" -> https://www.khronos.org/opengl/wiki/OpenGL_Error#Meaning_of_errors", err);
        }
        return success && (err == GL_NO_ERROR);
}

void log_world(struct scene_obj *world, int obj_c) {
        struct scene_obj curr;
        char *out_str = calloc(MAX_PARAM_NAME, sizeof(char));
        int dims;

        for (int i = 0; i < obj_c; ++i) {
                curr = world[i];

                switch (curr.type) {
                case SPHERE:
                        dims = 1; // 1 dimensions - just radius
                        strcpy(out_str, "SPHERE");
                        break;
                case CUBOID:
                        dims = 3; // 3 dimensions - width, height, depth
                        strcpy(out_str, "CUBOID");
                        break;
                case PLANE:
                        dims = 2; // 2 dimensions - width, height
                        strcpy(out_str, "PLANE");
                        break;
                default:
                        dims = 0; // something has gone awry, leave it
                        break;
                }

                log("\tobject %d:", i);
                log("\t - type             : %s", out_str);
                log("\t - coords (x, y, z) : %.2f, %.2f, %.2f", curr.coords[0], curr.coords[1], curr.coords[2]);
                log("\t - albedo (r, g, b) : %.2f, %.2f, %.2f", curr.albedo[0], curr.albedo[1], curr.albedo[2]);

                for (int j = 0; j < MAX_PARAM_NAME; ++j) {
                        out_str[j] = NL_C;

                        if (j < dims) {
                                sprintf(out_str, "%s%.2f", out_str, curr.dims[j]);

                                if (j < dims - 1) {
                                        sprintf(out_str, "%s, ", out_str);
                                }
                        }
                }
                log("\t - dimensions       : %s", out_str);

                for (int j = 0; j < MAX_PARAM_NAME; ++j) {
                        out_str[j] = NL_C;
                }
                switch (curr.mat) {
                case MATT:
                        strcpy(out_str, "MATTE");
                        break;
                case SHNY:
                        strcpy(out_str, "SHINY");
                        break;
                case REFL:
                        strcpy(out_str, "REFLECTIVE");
                        break;
                case GLSS:
                        strcpy(out_str, "GLASS");
                        break;
                case LGHT:
                        strcpy(out_str, "LIGHT");
                        break;
                case CMRA:
                        strcpy(out_str, "CAMERA");
                        break;
                default:
                        break;
                }
                log("\t - material         : %s", out_str);
        }

        free(out_str);
        out_str = NULL;
}