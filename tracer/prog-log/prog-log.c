#include "prog-log.h"

int weights[5] = { 2, 2, 1, 4, 3 };

int prog(enum STAGE current) {
        printf("\rprogress  : ");

        for (int i = 1; i < current; ++i) {
                print_prog(DONE, weights[i]);
        }

        print_prog(DOING, weights[current]);

        for (int i = current + 1; i < COMPLETE; ++i) {
                print_prog(TODO, weights[i]);
        }

        printf("\t");
}

void print_prog(enum STATUS stat, int width) {
        for (int i = 0; i < width; ++i) {
                printf("%c", stat);
        } 
}

int advance(int *current) {
        (*current)++;
        char *msg = calloc(MAX_MSG_LEN, sizeof(char));
        if (!get_msg(*current, &msg)) {
                return FALSE;
        }

        prog(*current);
        log("currently: %s", msg);
        printf("currently : %s\t\t\t", msg);
        return TRUE;
}

int get_msg(enum STAGE current, char **msg) {
        switch (current) {
        case CONFIG:
                strcpy(*msg, "fetching configuration variables");
                break;
        case SCENE:
                strcpy(*msg, "fetching scene data");
                break;
        case INIT:
                strcpy(*msg, "initialising renderer");
                break;
        case COMPUTE:
                strcpy(*msg, "computing render");
                break;
        case STORE:
                strcpy(*msg, "storing render");
                break;
        case COMPLETE:
                strcpy(*msg, "rendering completed");
                break;
        default:
                return FALSE;
        }

        return TRUE;
}