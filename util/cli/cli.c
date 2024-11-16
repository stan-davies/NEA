#include "cli.h"

enum PROGS take_input(int argc, char **argv) {
        if (argc <= 1) {
                log_err("no command given");
                return NONE;
        }

        enum PROGS cmd = check_cmd(argv[1]);
        if (NONE == cmd) {
                log_err("invalid command given");
                return NONE;
        }
        
        
        // check args

        return 0;
}

enum PROGS check_cmd(char **cmd_str) {
        enum PROGS cmd = NONE;

        if (0 == strcmp(cmd_str, "render")) {
                cmd = REND;
        } else if (0 == strcmp(cmd_str, "edit")) {
                cmd = EDIT;
        } else {
                log_err("invalid command given at symbol '%s'", cmd_str);
        }

        return cmd;
}

int cmd_to_str(enum PROGS cmd, char **str) {
        *str = (char *)malloc(MAX_CMD_STR_LEN * sizeof(char));

        switch (cmd) {
        case REND:
                strcpy(*str, "RENDER");
                break;
        case EDIT:
                strcpy(*str, "EDIT");
                break;
        case NONE:
                strcpy(*str, "NONE");
                break;
        default:
                strcpy(*str, "INVALID");
                return FALSE;
                break;
        }

        return TRUE;
}