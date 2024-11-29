#ifndef PROG_LOG_H
#define PROG_LOG_H

#include "file-handling/log-writer/log-writer.h"

#define MAX_MSG_LEN 40

enum STAGE {
        BEGIN,
        CONFIG,
        SCENE,
        INIT,
        COMPUTE,
        STORE,
        COMPLETE
};

enum STATUS {
        DONE  = 35,  // #
        DOING = 126, // ~
        TODO  = 45   // -
};

extern int weights[5];

void prog(enum STAGE current);

void print_prog(enum STATUS stat, int width);

int advance(int *current);

/*
 *   INPUT  : Current stage. Pointer to string for message.
 *   OUTPUT : Whether current is a valid stage or not.
 * 
 *   DESC   : Determines relevant message for the current stage of rendering.
 */
int get_msg(enum STAGE current, char **msg);

#endif