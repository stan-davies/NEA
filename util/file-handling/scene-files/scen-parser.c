#include "scen-parser.h"

int create_world(char *path, struct scene_obj **world, int *object_count) {
        char *cnt;
        int cntc;

        if (!parse(path, &cnt, &cntc)) {
                return FALSE;
        }

        char *cnt_ptr = cnt;
        char *line = calloc(MAX_LINE_LENGTH, sizeof(char));
        char *line_ptr = line;
        int line_len;
        struct scene_obj curr_obj;

        // delegate?
        if (yield_split(&cnt_ptr, &line, &line_len, LF_C, MAX_LINE_LENGTH)) {
                int objc = atoi(line);
                if (objc < 1 || objc > MAX_OBJ_COUNT) {
                        log_err("invalid object count");
                        goto clear1;
                }

                *object_count = objc;
                *world = malloc(objc * sizeof(struct scene_obj));
        } else {
                log_err("invalid scene file");
                goto clear1;
        }

        // this isn't a list of parameters, it is a single parameter, so this sizing makes no sense
        char *chunk = calloc(MAX_OBJ_PARAMS, sizeof(char));
        int chunk_len;

        int obj_c = 0;

        float curr_arg;

        int arg_c = 0;

        while (yield_split(&cnt_ptr, &line, &line_len, LF_C, MAX_LINE_LENGTH)) {
                log("remaining content: %s", cnt_ptr);
                log("extracted: %s\n---\n", line);
                switch (line[0]) {
                case SL_C:
                        goto cont;
                case NL_C:
                        goto cont;
                case SPHERE:
                        break;
                case CUBOID:
                        break;
                case PLANE:
                        break;
                default:
                        log_err("invalid object found at '%s'", line);
                        goto clear2;
                }

                curr_obj.type = line[0];
                line[0] = SP_C;

                arg_c = 0;

                for (int i = 0; i < MAX_OBJ_PARAMS; ++i) {
                        if (!yield_split(&line_ptr, &chunk, &chunk_len, CM_C, MAX_OBJ_PARAMS)) {
                                break;
                        }

                        if (chunk[0] > CHR_9) {  // need a stronger check here, combine with 'check valid num?'
                                log("potential material: %d", chunk[0]);
                                curr_obj.mat = chunk[0];
                                // break?
                        } else {
                                log("potential something: %s", chunk);
                                // introduce 'check valid num' function, maybe even a custom atof
                                curr_arg = atof(chunk);
                                log("it was: %.2f", curr_arg);

                                *(&curr_obj.coords[0] + arg_c) = curr_arg;
                                arg_c++;
                        }

                        // delegate to clear string with 'cont:'
                        for (int j = 0; j < MAX_OBJ_PARAMS; ++j) {
                                chunk[j] = 0;
                        }
                }

                // the curr_obj is not being updated on second pass
                (*world)[obj_c] = curr_obj;
                obj_c++;

                if (obj_c > *object_count) {
                        log_err("too many objects given");
                        goto clear2;
                }

                cont:
                // delegate to 'clear_line'
                for (int i = 0; i < MAX_LINE_LENGTH; ++i) {
                        line[i] = 0;
                }
        }

        free(cnt);
        free(chunk);
        free(line);
        
        return TRUE;

        clear2:
        free(cnt);
        free(chunk);
        clear1:
        free(line);

        return FALSE;
}