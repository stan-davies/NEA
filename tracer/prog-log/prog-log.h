#ifndef PROG_LOG_H
#define PROG_LOG_H

#include "file-handling/log-writer/log-writer.h"
#include "file-handling/scene-files/scen-struct.h"

#define MAX_MSG_LEN 40

enum STAGE {
        BEGIN,
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

extern int weights[COMPLETE - 1];

/*
 *   INPUT  : Current stage of rendering.
 *   OUTPUT : -
 * 
 *   DESC   : Outputs the current progress of the render. This is the
 *            combination of a loading bar and an informative messgae.
 */
void prog(enum STAGE current);

/*
 *   INPUT  : The status of the current stage. The stages weight.
 *   OUTPUT : -
 * 
 *   DESC   : Outputs the character `stat` `width` number of times. This will
 *            make up each chunk of the progress bar.
*/
void print_prog(enum STATUS stat, int width);

/*
 *   INPUT  : A pointer to the current stage of rendering.
 *   OUTPUT : Success in advancing the stage.
 * 
 *   DESC   : Advances the current rendering stage to the next and updates the
 *            progress messages.
 */
int advance(int *current);

/*
 *   INPUT  : Current stage. Pointer to string for message.
 *   OUTPUT : Whether current is a valid stage or not.
 * 
 *   DESC   : Determines relevant message for the current stage of rendering.
 */
int get_msg(enum STAGE current, char **msg);

#endif