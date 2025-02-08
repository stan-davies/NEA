#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "global.h"
#include "opengl/gl-init.h"
#include "cli/cli.h"
#include "dispose/dispose.h"

int main(int argc, char **argv) {
        init_log();

        enum PROGS cmd = take_input(argc, argv);
        if (NONE == cmd) {
                log_err("could not start program");
                return 0;
        }

        log_vars(cmd);

        GLFWwindow *window;
        init_gl(cmd, window);

        log("----------\n");

        int success;

        switch(cmd) {
        case REND:
                success = dispose_renderer(argc, argv);
                break;
        case HELP:
                success = TRUE;
                help();
                break;
        default:
                success = FALSE;
                break;
        }

        if (!success) {
                printf("\n\nERROR: Program failed to run. See `.log` for further details.\n");
                log_err("Program failed to run.");
        } else {
                printf("\n\nThe program executed successfully. Find further details of execution at `.log`.");
                log("Program executed successfully.");
        }

        term_gl();

        return 0;
}