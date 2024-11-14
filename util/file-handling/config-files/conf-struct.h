#ifndef CONF_STRUCT_H
#define CONF_STRUCT_H

enum DATA {
        DIMENSIONS,
        SAMPLES
};

struct config_var_node {
        enum DATA type;
        union {
                int   dat;
                int   num;
                float flt;
                int   i2[2];
        };

        int *next;
};

int is_type(char *name);

void create_var_list(int *root);

int add_var_node(enum DATA type, int dat, int *ptr);

// go through each config var, so that the full set of stuff can be defined, with these pesky little folks getting subbed in where necessary
int traverse_var_list(int *root);

#endif