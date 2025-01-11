#ifndef SCEN_STRUCT_H
#define SCEN_STRUCT_H

#define MAX_OBJ_COUNT  128

enum OBJS {
        SPHERE = 83, // 'S'
        CUBOID = 67, // 'C'
        PLANE  = 80, // 'P'
        NAO    = 0,  // Not An Object
};

enum MATS {
        MATT = 77,
        SHNY = 83,
        REFL = 82,
        GLSS = 71,
        LGHT = 76,
        CMRA = 67,
};

// COLOUR
struct scene_obj {
        enum OBJS type;
        float coords[3];
        float dims[3]; // sphere uses only 0 (radius), plane uses 0 & 1 (width, height), cuboid uses all 3 (width, height depth)
        enum MATS mat;
        float albedo[3];
};

#endif