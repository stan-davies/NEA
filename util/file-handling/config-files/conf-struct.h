#ifndef CONF_STRUCT_H
#define CONF_STRUCT_H

#include "global.h"

enum CONF {
	IMAGE_DIMS,   // int2
	MAX_SAMPLES,  // int
	MAX_BOUNCES,  // int
	DF_DIST,      // float
	DF_ANGLE,     // float
        NUM_CONFS     // len(config)
};

enum TYPE {
	INT,
	FLT,
	INT2
};

struct config_var {
        enum CONF conf;
        enum TYPE type;
        union {
                int   dat;
                int   num;
                float flt;
                int   i2[2];
        };
};

#endif