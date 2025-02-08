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

int read_args_rend(int argc, char **argv, float *vfov, int *width, int *height, int *max_bounces, int *max_samples, char **output_f, char **scene_file) {
        int opt;
        while (-1 != (opt = getopt(argc, argv, "f:w:h:m:b:o:s:"))) {
                switch (opt) {
                case 'f':
                        if (!valid_arg(optarg, FLT)) {
                                log_err("Invalid argument given for option 'vfov'.");
                                return FALSE;
                        }
                        *vfov = atof(optarg);
                        log("Vertical field of view given as %.2f.", *vfov);
                        break;
                case 'w':
                        if (!valid_arg(optarg, INT)) {
                                log_err("Invalid argument given for option 'image width'.");
                                return FALSE;
                        }
                        *width = atoi(optarg);
                        log("Renderframe width given as %.2f.", *width);
                        break;
                case 'h':
                        if (!valid_arg(optarg, INT)) {
                                log_err("Invalid argument given for option 'image height'.");
                                return FALSE;
                        }
                        *height = atoi(optarg);
                        log("Renderframe height given as %.2f.", *height);
                        break;
                case 'm':
                        if (!valid_arg(optarg, INT)) {
                                log_err("Invalid argument given for option 'max samples'.");
                                return FALSE;
                        }
                        *max_samples = atoi(optarg);
                        log("Max samples given as %d.", *max_samples);
                        break;
                case 'b':
                        if (!valid_arg(optarg, INT)) {
                                log_err("Invalid argument given for option 'max bounces'.");
                                return FALSE;
                        }
                        *max_bounces = atoi(optarg);
                        log("Max bounces given as %d.", *max_bounces);
                        break;
                case 'o':
                        if (!valid_fp(optarg) || strlen(optarg) >= MAX_FILENAME_LENGTH) {
                                log_err("Invalid argument given for option 'output path'.");
                                return FALSE;
                        }
                        sprintf(*output_f, "%s", optarg);
                        break;
                case 's':
                        if (!valid_fp(optarg) || strlen(optarg) >= MAX_FILENAME_LENGTH) {
                                log_err("Invalid argument given for option 'scene file'.");
                                return FALSE;
                        }
                        sprintf(*scene_file, "%s", optarg);
                        break;
                default:
                        log_err("Invalid option given at symbol '%s'.", opt);
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

int valid_fp(char *fp) {
        char c = NL_C;
        int valid;
        for (int i = 0; i < strlen(fp); ++i) {
                c = fp[i];

                // is uppercase, lowercase, '.', '_' or '-'
                valid = (c >= CHR_A && c <= CHR_Z) || (c >= CHR_a && c <= CHR_z) || PT_C == c || UND_C == c || DSH_C == c;

                if (!valid) {
                        log_err("Invalid path given, filename must not contain symbol '%c'", c);
                        return FALSE;
                }
        }

        return TRUE;
}

enum PROGS check_cmd(char **cmd_str) {
        enum PROGS cmd = NONE;

        if (0 == strcmp(cmd_str, "render")) {
                cmd = REND;
        } else if (0 == strcmp(cmd_str, "help")) {
                cmd = HELP;
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
        case HELP:
                strcpy(*str, "HELP");
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

void help() {
        log("%s\n%s\n%s\n%s\n%s", WLCME_INFO, PARAM_HELP, SCENE_HELP, OUTPT_HELP, OPRTN_HELP);
        printf("%s\n%s\n%s\n%s\n%s", WLCME_INFO, PARAM_HELP, SCENE_HELP, OUTPT_HELP, OPRTN_HELP);
}