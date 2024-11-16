#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "glob.h"
#include "opengl/gl-init.h"
#include "cli/cli.h"

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

        switch(cmd) {
        case REND:
                // do render
                break;
        case EDIT:
                // do edit
                break;
        default:
                break;
        }

        term_gl();

        return 0;
}