#include "prog-log.h"

int weights[COMPLETE - 1] = { 1, 2, 4, 3 };

void prog(enum STAGE current) {
        printf("\rprogress: ");

        for (int i = 0; i < current - 1; ++i) {
                print_prog(DONE, weights[i]);
        }

        if (current < COMPLETE) {
                print_prog(DOING, weights[current - 1]);
        }

        for (int i = current; i < COMPLETE - 1; ++i) {
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
        if ((*current) + 1 > COMPLETE) {
                log_err("Cannot advance stage any further.");
                return FALSE;
        }

        (*current)++;
        char *msg = calloc(MAX_MSG_LEN, sizeof(char));
        if (!get_msg(*current, &msg)) {
                log_err("Invalid stage requested.");
                return FALSE;
        }

        prog(*current);
        log("%s...", msg);
        printf("currently: %s     ", msg);

        return TRUE;
}

int get_msg(enum STAGE current, char **msg) {
        switch (current) {
        case SCENE:
                strcpy(*msg, "Fetching scene data");
                break;
        case INIT:
                strcpy(*msg, "Initialising renderer");
                break;
        case COMPUTE:
                strcpy(*msg, "Computing render");
                break;
        case STORE:
                strcpy(*msg, "Storing render");
                break;
        case COMPLETE:
                strcpy(*msg, "Rendering completed");
                break;
        default:
                return FALSE;
        }

        return TRUE;
}