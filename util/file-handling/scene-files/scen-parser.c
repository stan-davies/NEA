#include "scen-parser.h"

int create_world(char *path, struct scene_obj **world, int *object_count) {
        char *cnt;
        int cntc;

        if (!parse(path, &cnt, &cntc)) {
                log_err("Could not read scene file.");
                return FALSE;
        }

        char *cnt_ptr = cnt;
        char *line = calloc(MAX_LINE_LENGTH, sizeof(char));
        int line_len;

        // delegate?
        if (yield_split(&cnt_ptr, &line, &line_len, LF_C, MAX_LINE_LENGTH)) {
                int objc = atoi(line);
                if (objc < 1 || objc > MAX_OBJ_COUNT) {
                        log_err("Invalid object count.");
                        goto clearline;
                }

                *object_count = objc;
                *world = malloc(objc * sizeof(struct scene_obj));
        } else {
                log_err("Invalid scene file.");
                goto clearline;
        }

        char *chunk = calloc(MAX_PARAM_LEN, sizeof(char));
        int chunk_len;

        char *line_ptr = line;
        
        struct scene_obj curr_obj;
        int obj_c = 0;

        float curr_arg;

        int arg_c = 0;

        while (yield_split(&cnt_ptr, &line, &line_len, LF_C, MAX_LINE_LENGTH)) {
                if (!choose_type(&curr_obj.type, line[0])) {
                        log_err("Invalid object found at '%s'.", line);
                        goto clearall;
                }

                if (0 == curr_obj.type) { // see `choose_type`/DESC for `0`
                        goto cont;
                }

                line[0] = SP_C;

                arg_c = 0;
                line_ptr = line;

                for (;;) {
                        if (!yield_split(&line_ptr, &chunk, &chunk_len, CM_C, MAX_PARAM_LEN)) {
                                break;
                        }

                        enum ARG_TYPE arg = get_arg_type(chunk, chunk_len);

                        switch (arg) {
                        case ARG_MAT:
                                curr_obj.mat = chunk[0];
                                break;
                        case ARG_FLT:
                                curr_arg = atof(chunk);
                                *(&curr_obj.coords[0] + arg_c) = curr_arg;
                                arg_c++;
                                break;
                        default:
                                log_err("Invalid argument at symbol '%s'.", chunk);
                                goto clearall;
                        }

                        clear_str(&chunk, MAX_PARAM_LEN);
                }

                if (obj_c >= *object_count) {
                        log_err("Too many objects given.");
                        goto clearall;
                }

                (*world)[obj_c] = curr_obj;
                obj_c++;

                cont:
                clear_str(&line, MAX_LINE_LENGTH);
        }

        free(cnt);
        free(chunk);
        free(line);
        
        return TRUE;

        clearall:
        free(cnt);
        free(chunk);
        clearline:
        free(line);

        return FALSE;
}

int choose_type(int *type, char line0) {
        *type = NAO;
        switch (line0) {
        case SL_C:
                break;
        case NL_C:
                break;
        case SPHERE:
                *type = SPHERE;
                break;
        case CUBOID:
                *type = CUBOID;
                break;
        case PLANE:
                *type = PLANE;
                break;
        default:
                return FALSE;
        }

        return TRUE;
}

void clear_str(char **str, int len) {
        for (int i = 0; i < len; ++i) {
                (*str)[i] = NL_C;
        }
}

enum ARG_TYPE get_arg_type(char *arg, int len) {
        enum ARG_TYPE status = ARG_INV;

        for (int i = 0; i < len; ++i) {
                if (NL_C == arg[i]) {
                        break;
                }

                if ((arg[i] >= CHR_0 && arg[i] <= CHR_9) || PT_C == arg[i]) {
                        if (ARG_MAT == status) {
                                return ARG_INV;
                        }
                        status = ARG_FLT;
                        continue;
                }

                switch (arg[i]) {
                case MATT:
                        break;
                case SHNY:
                        break;
                case REFL:
                        break;
                case GLSS:
                        break;
                case LGHT:
                        break;
                default:
                        return ARG_INV;
                }

                status = ARG_MAT;
        }

        return status;
}