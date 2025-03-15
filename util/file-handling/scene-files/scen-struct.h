#ifndef SCEN_STRUCT_H
#define SCEN_STRUCT_H

/*
 * If this needs to be altered, don't forget to also alter it on the GPU side.
 * This is in `structs.glsl`. Do also note than any higher greater than 100
 * is not acceptable for the GPU copy of the array that this is used to create.
 * By 'not acceptable' I mean the compute program won't link if this is too
 * high, and that leads to a super confusing and irritating error which I have
 * just spent all day fixing.
 */
#define MAX_OBJ_COUNT 16

enum OBJS {
        SPHERE = 83, // 'S'
        PLANE  = 80, // 'P'
        CAMERA = 67, // 'C'
        NAO    = 0,  // Not An Object
};

enum MATS {
        MATT = 77, // 'M'
        SHNY = 83, // 'S'
        REFL = 82, // 'R'
        GLSS = 71, // 'G'
        LGHT = 76, // 'L'
        CMRA = 67, // 'C'
};

struct scene_obj {
        enum OBJS type;
        float coords[3];
        float albedo[3];
        float dims[3];
        enum MATS mat;
};

#endif