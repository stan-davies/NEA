#ifndef SCEN_STRUCT_H
#define SCEN_STRUCT_H

// camera
/*
 - add a camera obj
 - repurpose dims as the view direction
 - ignore material and put focal length (float) in config
*/

enum OBJS {
        SPHERE = 83, // 'S'
        CUBOID = 67, // 'C'
        PLANE  = 80, // 'P'
};

enum MATS {
        MATT = 77,
        SHNY = 83,
        REFL = 82,
        GLSS = 71,
        LGHT = 76
};

struct scene_obj {
        enum OBJS type;
        float coords[3];
        float dims[3]; // sphere uses only 0 (radius), plane uses 0 & 1 (width, height), cuboid uses all 3 (width, height depth)
        enum MATS mat;
};

#endif