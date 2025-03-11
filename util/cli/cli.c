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

int read_args_rend(int argc, char **argv, float *vfov, int *width, int *height, int *max_bounces, int *max_samples, float *ambient_coef, char **output_f, char **scene_f) {
        float tmp_f;
        int tmp_i;

        int opt;
        while (-1 != (opt = getopt(argc, argv, "f:w:h:m:b:a:o:s:"))) {
                switch (opt) {
                case 'f':
                        if (!valid_arg(optarg, FLT, MIN_VFOV, MAX_VFOV)) {
                                bad_value_err(opt);
                                return FALSE;
                        }

                        tmp_f = atof(optarg);
                        if (tmp_f < MIN_VFOV || tmp_f > MAX_VFOV) {
                                bad_value_err(opt);
                                return FALSE;
                        }

                        *vfov = tmp_f;
                        log("Vertical field of view given as %.2f.", *vfov);
                        break;
                case 'w':
                        if (!valid_arg(optarg, INT, MIN_DIMENSION, MAX_DIMENSION)) {
                                bad_value_err(opt);
                                return FALSE;
                        }

                        tmp_i = atoi(optarg);
                        if (tmp_i < MIN_DIMENSION || tmp_i > MAX_DIMENSION) {
                                bad_value_err(opt);
                                return FALSE;
                        }

                        *width = tmp_i;
                        log("Renderframe width given as %d.", *width);
                        break;
                case 'h':
                        if (!valid_arg(optarg, INT, MIN_DIMENSION, MAX_DIMENSION)) {
                                bad_value_err(opt);
                                return FALSE;
                        }

                        tmp_i = atoi(optarg);
                        if (tmp_i < MIN_DIMENSION || tmp_i > MAX_DIMENSION) {
                                bad_value_err(opt);
                                return FALSE;
                        }

                        *height = tmp_i;
                        log("Renderframe height given as %d.", *height);
                        break;
                case 'm':
                        if (!valid_arg(optarg, INT, MIN_SAMPLES, MAX_SAMPLES)) {
                                bad_value_err(opt);
                                return FALSE;
                        }

                        tmp_i = atoi(optarg);
                        if (tmp_i < MIN_SAMPLES || tmp_i > MAX_SAMPLES) {
                                bad_value_err(opt);
                                return FALSE;
                        }

                        *max_samples = tmp_i;
                        log("Max samples given as %d.", *max_samples);
                        break;
                case 'b':
                        if (!valid_arg(optarg, INT, MIN_BOUNCES, MAX_BOUNCES)) {
                                bad_value_err(opt);
                                return FALSE;
                        }

                        tmp_i = atoi(optarg);
                        if (tmp_i < MIN_BOUNCES || tmp_i > MAX_BOUNCES) {
                                bad_value_err(opt);
                                return FALSE;
                        }

                        *max_bounces = tmp_i;
                        log("Max bounces given as %d.", *max_bounces);
                        break;
                case 'a':
                        if (!valid_arg(optarg, FLT, MIN_AMB_COEF, MAX_AMB_COEF)) {
                                bad_value_err(opt);
                                return FALSE;
                        }

                        tmp_f = atof(optarg);
                        if (tmp_f < MIN_AMB_COEF || tmp_f > MAX_AMB_COEF) {
                                bad_value_err(opt);
                                return FALSE;
                        }

                        *ambient_coef = tmp_f;
                        log("Ambient lighting coefficient given as %.2f.", *ambient_coef);
                        break;
                case 'o':
                        if (!valid_fp(optarg) || strlen(optarg) >= MAX_PATH_LENGTH) {
                                log("Option for parameter 'output file' does not meet conditions.");
                                return FALSE;
                        }

                        sprintf(*output_f, "%s", optarg);
                        log("Output file given as '%s'.", *output_f);
                        break;
                case 's':
                        if (!valid_fp(optarg) || strlen(optarg) >= MAX_PATH_LENGTH) {
                                log("Option for parameter 'scene file' does not meet conditions.");
                                return FALSE;
                        }
                        
                        sprintf(*scene_f, "%s", optarg);
                        log("Scene file given as '%s'.", *scene_f);
                        break;
                default:
                        log_err("Invalid option given at symbol '%s'.", opt);
                        break;
                }
        }

        return TRUE;
}

int valid_arg(char *arg, enum TYPES type, float min, float max) {
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

        int n;

        if (FLT == type) {
                n = (int)(atof(arg));
        } else {
                n = atoi(arg);
        }

        if (n < min || n > max) {
                return FALSE;
        }        

        return TRUE;
}

int valid_fp(char *fp) {
        char c = NL_C;
        int valid;
        for (int i = 0; i < strlen(fp); ++i) {
                c = fp[i];

                // is uppercase, lowercase, '.', '_', '-' or '/'
                valid = (c >= CHR_A && c <= CHR_Z) || (c >= CHR_a && c <= CHR_z) || PT_C == c || UND_C == c || DSH_C == c || SL_C == c;

                if (!valid) {
                        log_err("Invalid path given, filename must not contain symbol '%c'", c);
                        return FALSE;
                }
        }

        return TRUE;
}

void bad_value_err(char param) {
        float min;
        float max;
        char *param_name = calloc(MAX_LINE_LENGTH, sizeof(char));
        char *valid_type = calloc(MAX_LINE_LENGTH, sizeof(char));

        switch (param) {
        case 'f':
                min = MIN_VFOV;
                max = MAX_VFOV;
                strcpy(param_name, "vertical field of view");
                strcpy(valid_type, "FLOAT");
                break;
        case 'w':
                min = MIN_DIMENSION;
                max = MAX_DIMENSION;
                strcpy(param_name, "image width");
                strcpy(valid_type, "INTEGER");
                break;
        case 'h':
                min = MIN_DIMENSION;
                max = MAX_DIMENSION;
                strcpy(param_name, "image height");
                strcpy(valid_type, "INTEGER");
                break;
        case 'm':
                min = MIN_SAMPLES;
                max = MAX_SAMPLES;
                strcpy(param_name, "max samples");
                strcpy(valid_type, "INTEGER");
                break;
        case 'b':
                min = MIN_BOUNCES;
                max = MAX_BOUNCES;
                strcpy(param_name, "max bounces");
                strcpy(valid_type, "FLOAT");
                break;
        case 'a':
                min = MIN_AMB_COEF;
                max = MAX_AMB_COEF;
                strcpy(param_name, "ambient lighting coefficient");
                strcpy(valid_type, "FLOAT");
                break;
        default:
                goto end;
                break;
        }

        log_err("Invalid value given for option %s. Expecting %s in interval [%1.f, %.1f].", param_name, valid_type, min, max);

        end:
        free(param_name);
        free(valid_type);
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