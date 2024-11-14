#ifndef SCEN_STRUCT_H
#define SCEN_STRUCT_H

enum OBJS {
        SPHERE,
        CUBOID,
        PLANE,
};

enum MATS {
        MATTE,
        GLOSSY,
        REFLECTIVE,
        GLASS,
        LIGHT
};

struct scene_obj_node {
        enum OBJS type;
        float coords[3];
        float dims[3]; // sphere uses only 0 (radius), plane uses 0 & 1 (width, height), cuboid uses all 3 (width, height depth)
        enum MATS mat;

        int *next;
};

int is_type(char *name);

void create_obj_list(int *root);

int add_obj_node(enum DATA type, float *coords, float *dims, enum MATS mat, int *ptr);

// go through each obj, so that each can be passed to the renderer sequentially or SUMTHIN
int traverse_obj_list(int *root);

#endif