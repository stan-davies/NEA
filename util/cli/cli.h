#ifndef CLI_H
#define CLI_H

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "global.h"
#include "file-handling/log-writer/log-writer.h"
#include "file-handling/parse.h"
#include "tracer/rend_const.h"

/*
 *   INPUT  : `argc` and `argv` as given to `main` when program is run.
 *   OUTPUT : Command that has been chosen, or `NONE` for any errors.
 * 
 *   DESC   : Takes an input command and determines which major command has
 *            given.
 */
enum PROGS take_input(int argc, char **argv);

enum TYPES {
        INT,
        FLT
};

/*
 *   INPUT  : `argc` and `argv` as given to `main` when program is run. Pointer
 *            to float for a given vertical fov. Pointer to an integer for a
 *            given image width. Pointer to an integer for a given image 
 *            height. Pointer to integer for maximum number of bounces per ray. 
 *            Pointer to integer for maximum number of samples per ray. Pointer 
 *            to float for ambient lighting coefficient. Pointer to string for 
 *            output file path. Pointer to string for scene file path.
 *   OUTPUT : Whether or not *all* options were valid.
 * 
 *   DESC   : Goes through each option given in `argv` and gets any relevant
 *            data from it. These data will be placed into the function
 *            arguments.
 */
int read_args_rend(int argc, char **argv, float *vfov, int *width, int *height, int *max_bounces, int *max_samples, float *ambient_coef, char **output_f, char **scene_f);

/*
 *   INPUT  : String containing argument to check. What data type the argument
 *            should be.
 *   OUTPUT : If the argument is valid, and can therefore be safely converted.
 * 
 *   DESC   : Ensures the given argument contains only digits, and potentially
 *            a single decimal separator if it is a floating point number.
 */
int valid_arg(char *arg, enum TYPES type, float min, float max);

/*
 *   INPUT  : String containing file path to check.
 *   OUTPUT : If the filepath is valid.
 * 
 *   DESC   : Checks the validity of the given file path. A valid path may
 *            contain letters, '.', '-' and '_'.
 */
int valid_fp(char *fp);

/*
 *   INPUT  : Parameter for which a bad value has been given.
 *   OUTPUT : -
 * 
 *   DESC   : Outputs an error message describing the format in which a value
 *            for the given parameter *should* be given - data type and valid
 *            interval.
 */
void bad_value_err(char param);

/*
 *   INPUT  : Choice of command as given in main args.
 *   OUTPUT : Command code, or `NONE` for anything unexpected.
 * 
 *   DESC   : Converts command word to command code and validates it.
 */
enum PROGS check_cmd(char **cmd_str);

/* 
 * Maximum length of string that describes each command. Includes room for 
 * `\0`.
 */
#define MAX_CMD_STR_LEN 8

/*
 *   INPUT  : Command to get string for. Pointer to string.
 *   OUTPUT : Whether or not the command given is valid.
 * 
 *   DESC   : Converts a command code to a string describing it.
 */
int cmd_to_str(enum PROGS cmd, char **str);

#define WLCME_INFO "Welcome to SPT! This is a path tracing renderer. The follow\
ing paragraphs will allow you to familiarise yourself with the program.\n"
#define PARAM_HELP "Paramters\n\nThe program allows several parameters, each \
of which controls some aspect of the rendering. These are:\n - 'f' vertical \
field of view of the camera (in degrees, [0.0, 180.0], default 20.0)\n - 'w' \
width of the output image (in pixels, [0, 2000], default 100)\n - 'h' height of\
 the output image (in pixels, [0, 2000], default 100)\n - 'm' maximum samples \
per ray (in [1, 500], default 3)\n - 'b' maximum bounces per ray (in [1, 200] \
default 3)\n - 'a' ambient lighting coefficient (in [0.0, 1.0], default 0.0) \n\
 - 'o' destination for the output image (as a path, default \"image.ppm\")\n - \
's' source of the scene file (as a path, default \"worlds/.world\")\nTo \
set one of the paramters, write its letter with a single hyphen beforehand. For\
 example:\n\n > spt render -f \"out.ppm\" -w 200.\n\n If you choose not to set \
any of the parameters, the default values will be used.\n"
#define SCENE_HELP "Scene Parameters:\n\nYou are able to create a custom scene \
file which describes the scene that you want to render. This requires a \
specific format in order to be understood by the program correctly. Every scene\
 file begins with a line that contains only a single number. This is the count \
of all the objects in your scene. It may not exceed 16. After this, you will \
write each of your objects. These take the form of a type and then a list of \
parameters. These parameters must be in order and are comma separated. They \
will describe the position of the object, the colour of the object, the \
dimensions of the object, and the material of the object. For example, for a \
matte red unit sphere centred at the origin we would write:\n S0,0,0,1,0,0,1,M\
\nAlthough this example includes integers, floating point values can be given \
also. Notice that the colour red has been given in RGB channels, with each \
channel being given in the interval [0, 1]. The shape has been described by 'S'\
 but if you instead want a plane, then use P. The material has been given by 'M\
'. The valid materials are:\n - 'M' Matte\n - 'S' Shiny\n - 'R' Reflective\n - \
'G' Glass\n - 'L' Light\n - 'C' Camera\nEvery scene must contain one, and only \
one camera object. This will be the camera from which the world is viewed. For \
your camera, the position is still the position, but the dimensions will be \
used to describe the direction in which the camera faces. Therefore, you should\
 choose a vector which points towards the object you want centred. The easiest \
way of doing this is by centring the camera at the origin and having all other \
object be positioned relative to it. Then, the view direction of the camera can\
 be the same as the position of your primary object.\n"
#define OUTPT_HELP "Output:\n\nThe program produces a few outputs. Obviously, a\
 rendered image is one of these. This will be stored in PPM image format, which\
 is raw pixel data. Some systems do not natively support this file type, as it \
is less common than compressed types such as JPG or PNG. If your system is one \
of these, you may wish to either convert it online or open it in a special \
software such as Adobe Photoshop.\nThe program will also produce some output to\
 the console. This will be a loading bar showing the progress of the render, as\
 well as a message telling you what the program is currently doing. For most \
renders, these will fly past quicker than you can read them, but this will \
prove useful for slower renders, with lots of objects.\nThe program will also \
always produce a '.log' file. This file contains information about the graphics\
 capabilities of your computer, as well as any necessary information about the \
running of the program. For example, if the program meets any issues due to the\
data you have given it, you can read them here.\n"
#define OPRTN_HELP "Operation:\n\nSimply, this is a path tracer. It works by \
firing rays into the scene from the camera, and tracing the paths that they \
follow. If this path terminates at a light source, then the pixel will be lit, \
taking colour accumulated from every bounce it made. If not, then the pixel \
will be dark. The paths of each ray is governed by the objects with which it \
collides, and more information on how this works can be found in the design \
section.\n"

// note about length renders will take -> output help
// note about no light -> ambient illumination
// say how planes work a bit more
// ensuring scenes are phsycially possible -> specifically on planes of glass not making sense
// setting plane normals in the right direction

/*
 *   INPUT  : -
 *   OUTPUT : -
 * 
 *   DESC   : Logs and outputs the above defined information.
 */
void help();

#endif