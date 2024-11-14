#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "version.h"
#include "opengl/gl_init.h"

enum CMD {
        REND,
        EDIT,
        NONE
};

int main(int argc, char **argv) {
        GLFWwindow *window;

        init_gl(TRACE, window);

        return 0;
}

int cli(int argc, char **argv) {
        printf("running at version %s\n", VERSION);

        if (argc <= 1) {
                printf("ERROR: no command given\n");
                return 0;
        }

        char *cmd_str = argv[1];
        enum CMD cmd = NONE;

        if (0 == strcmp(cmd_str, "render")) {
                cmd = REND;
        } else if (0 == strcmp(cmd_str, "edit")) {
                cmd = EDIT;
        } else {
                printf("ERROR: invalid command given at symbol '%s'", cmd_str);
                return 0;
        }

        switch(cmd) {
        case REND:
                printf("you have chosen to render something\n");
                break;
        case EDIT:
                printf("you have chosen to edit something\n");
                break;
        default:
                break;
        }

        return 0;
}