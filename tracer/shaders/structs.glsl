struct ray {
        vec3 origin;
        vec3 dir;
};

struct object {
        int  type;
        vec3 coords;
        vec3 albedo;
        vec3 dims;
        int  mat;
};

/* 
 * Program will not link if this is any higher than 100. I do not really know
 * why but figuring that out was a pain so lets just take that as the Lords
 * will and not set it to anything higher than 100.
 */
#define MAX_OBJ_COUNT 8

struct hit_record {
        bool   collided;
        vec3   point;
        vec3   normal;
        object obj;
};

struct camera {
        vec3 pos;
        vec3 plane_00;
        vec3 plane_dx;
        vec3 plane_dy;
};