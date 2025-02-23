#ifndef REND_CONST_H
#define REND_CONST_H

// default configuration of input parameters
#define DEF_VFOV        20.f
#define DEF_IMG_WIDTH   100
#define DEF_IMG_HEIGHT  100
#define DEF_MAX_BOUNCES 3
#define DEF_MAX_SAMPLES 3
#define DEF_AMB_COEF    0.f
#define DEF_SF          ".world"
#define DEF_OF          "image.ppm"

// minimmum and maximum values for input parameters
#define MIN_VFOV       0.f
#define MAX_VFOV       90.f
#define MIN_DIMENSION  1.f
#define MAX_DIMENSION  2000.f
#define MIN_SAMPLES    1.f
#define MAX_SAMPLES    500.f
#define MIN_BOUNCES    1.f
#define MAX_BOUNCES    200.f
#define MIN_AMB_COEF   0.f
#define MAX_AMB_COEF   1.f

#endif