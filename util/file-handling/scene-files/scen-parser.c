#include "scen-parser.h"

int create_world(char *path, struct scene_obj **world, int *object_count) {
        char *cnt;
        int cntc;

        if (!parse(path, &cnt, &cntc)) {
                return FALSE;
        }

        char *cnt_ptr = cnt;
        char *line = calloc(MAX_LINE_LENGTH, sizeof(char));
        int line_len;
        struct scene_obj curr_obj;

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

        char *line_ptr = line;
        char *chunk = calloc(MAX_OBJ_PARAMS, sizeof(char));
        int chunk_len;

        int obj_c = 0;

        while (yield_split(&cnt_ptr, &line_ptr, &line_len, LF_C, MAX_LINE_LENGTH)) {
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

                for (int i = 0; i < ARGS; ++i) {
                        if (!yield_split(&line_ptr, &chunk, &chunk_len, CM_C, MAX_OBJ_PARAMS)) {
                                break;
                        }

                        if (chunk[0] > CHR_9) {
                                curr_obj.mat = chunk[0]; // what if it is wrong
                        } else {
                                float arg = atof(chunk); // returns 0 for invalid, could also be 0 properly...
                                *(&(curr_obj.type) + (i * sizeof(float))) = arg;
                        }

                        strcpy(chunk, "");
                }

                (*world)[obj_c] = curr_obj;
                obj_c++;

                cont:
                strcpy(line, "");
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