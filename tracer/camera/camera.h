#ifndef CAMERA_H
#define CAMERA_H

#include "global.h"
#include "file-handling/scene-files/scen-struct.h"

/*
 * Hopefully, this needs no introduction.
 */
#define PI 3.1415926535f

/*
 * Standardised upward direction. A default value of (0, 1, 0) is set in
 * `camera.c`. Doing this as so does not allow for the camera to have roll, but
 * if pitch and yaw isn't enough for you then I just don't know what to say.
 */
extern float vup[3];

struct camera {
        float pos[3];        // position of actual camera
        float plane_00[3];   // centre of top left pixel in viewing plane
        float plane_dx[3];   // unit vector parallel to base of viewing plane
        float plane_dy[3];   // unit vector parallel to height of viewing plane
};

/*
*please ohh please ohh pleaase! work!
 *   INPUT  : The array of scene objects making up the world. The count of
 *            scene objects in the world. A pointer to the camera object that
 *            is to be populated with data. The vertical field of the camera.
 *            The width of the image, in pixels, that is going to be rendered.
 *            The height of the image, in piixels, that is going to be 
 *            rendered.
 *   OUTPUT : Success in creating camera.
 * 
 *   DESC   : Finds the camera in the scene and constructs the components of it
 *            which are necessary during rendering. Lower in this file is a
 *            struct `camera`, this function is effecitvely populating that
 *            struct with data that it must first calculate.
 */
int create_camera(struct scene_obj *world, int obj_c, struct camera *cam, float vfov, int img_width, int img_height);

/*
 *   INPUT  : An angle, measured in degrees.
 *   OUTPUT : The same angle, measured in radians.
 * 
 *   DESC   : Converts an angle from degrees to radians.
 */
inline float deg_to_rad(float angle);

/*
 *   INPUT  : 3D vector to find magnitude of.
 *   OUTPUT : Magnitude of given vector.
 * 
 *   DESC   : Finds magnitude of given vector.
 */
float magnitude(float *vec);

/*
 *   INPUT  : A pointer to a 3D vector.
 *   OUTPUT : Whether or not the vector has length 0.
 * 
 *   DESC   : Takes the given 3D vector, divides it by its magnitude, and
 *            places the altered components back into the original vector.
 */
int normalise(float **vec);

/*
 *   INPUT  : A 3D vector. A scalar.
 *   OUTPUT : The scaled 3D vector.
 * 
 *   DESC   : Scales a 3D vector by the given scalar.
 */
float *scale(float *vec, float scl);

/*
 *   INPUT  : A 3D vector. Another 3D vector.
 *   OUTPUT : The sum of the two vectors.
 * 
 *   DESC   : Adds the two given 3D vectors.
 */
float *add(float *vec1, float *vec2);

/*
 *   INPUT  : A 3D vector. Another 3D vector.
 *   OUTPUT : The cross product of the two vectors.
 * 
 *   DESC   : Determines the cross product of the two given 3D vectors.
 */
float *cross(float *vec1, float *vec2);

/*
 *   INPUT  : A pointer to a 3D destination vector. A 3D source vector.
 *   OUTPUT : -
 * 
 *   DESC   : Sets the content of the destination vector to the content of the
 *            source vector.
 */
void vecset(float **vec1, float *vec2);

#endif