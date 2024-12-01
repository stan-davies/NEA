#include "conf-parser.h"

int construct_config(char *path, struct config_var **config) {
        char *cnt;
        int cntc;

        if (!parse(path, &cnt, &cntc)) {
                return FALSE;
        }

        *config = malloc(NUM_CONFS * sizeof(struct config_var));

        for (int i = 0; i < NUM_CONFS; ++i) {
                (*config)[i].conf = i;
                (*config)[i].type = 3; // how to link it to their type???
                (*config)[i].dat  = NULL;
        }

        free(cnt);
}