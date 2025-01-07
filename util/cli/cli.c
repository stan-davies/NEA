#include "cli.h"

enum PROGS take_input(int argc, char **argv) {
        if (argc <= 1) {
                log_err("No command given.");
                return NONE;
        }

        enum PROGS cmd = check_cmd(argv[1]);
        if (NONE == cmd) {
                log_err("Invalid command given.");
        }

        return cmd;
}

int read_args_rend(int argc, char **argv, float *focal_length, int *width, int *height) {
        int opt;
        while (-1 != (opt = getopt(argc, argv, "f:w:h:"))) {
                switch (opt) {
                case 'f':
                        if (!valid_arg(optarg, FLT)) {
                                log_err("Invalid argument given for option 'focal length'.");
                                return FALSE;
                        }
                        *focal_length = atof(optarg);
                        break;
                case 'w':
                        if (!valid_arg(optarg, INT)) {
                                log_err("Invalid argument given for option 'image width'.");
                                return FALSE;
                        }
                        *width = atoi(optarg);
                        break;
                case 'h':
                        if (!valid_arg(optarg, INT)) {
                                log_err("Invalid argument given for option 'image height'.");
                                return FALSE;
                        }
                        *height = atoi(optarg);
                        break;
                default:
                        log_err("invalid option given at symbol '%s'", opt);
                        break;
                }
        }

        return TRUE;
}

int valid_arg(char *arg, enum TYPES type) {
        char c;
        int pt = FALSE;

        for (int i = 0; ; ++i) {
                c = arg[i];

                if (NL_C == c) {
                        break;
                }

                if (FLT == type && PT_C == c && !pt) {
                        pt = TRUE;
                        continue;
                }

                if (c < CHR_0 || c > CHR_9) {
                        log_err("Invalid character found in argument '%s' at symbol '%c'.", arg, c);
                        return FALSE;
                }
        }

        return TRUE;
}

enum PROGS check_cmd(char **cmd_str) {
        enum PROGS cmd = NONE;

        if (0 == strcmp(cmd_str, "render")) {
                cmd = REND;
        } else if (0 == strcmp(cmd_str, "edit")) {
                cmd = EDIT;
        } else {
                log_err("Invalid command given at symbol '%s'.", cmd_str);
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