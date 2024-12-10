#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "global.h"
#include "opengl/gl-init.h"
#include "cli/cli.h"
#include "tracer/core.h"

#include "file-handling/scene-files/scen-parser.h"

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

        return test_world();





        int success;

        switch(cmd) {
        case REND:
                success = render();
                break;
        case EDIT:
                // do edit
                break;
        default:
                success = FALSE;
                break;
        }

        if (!success) {
                log_err("problem in program");
        }

        term_gl();

        return 0;
}

int test_world() {
        struct scene_obj *world;
        int obj_c;
        if (!create_world(".world", &world, &obj_c)) {
                log_err("could not create world");
                return FALSE;
        }

        struct scene_obj obj;
        for (int i = 0; i < obj_c; ++i) {
                obj = world[i];
                log("object %d:", i);
                log(" > type: %d", obj.type);
                log(" > coords: (%.2f, %.2f, %.2f)", obj.coords[0], obj.coords[1], obj.coords[2]);
                log(" > dims: [%.2f, %.2f, %.2f]", obj.dims[0], obj.dims[1], obj.dims[2]);
                log(" > mat: %d", obj.mat);
        }

        return TRUE;
}