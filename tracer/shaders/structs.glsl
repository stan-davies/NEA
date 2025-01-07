struct ray {
        vec3 origin;
        vec3 dir;
}

struct object {
        int  type;
        vec3 coords;
        vec3 dims;
        int  mat;
}

struct hit_record {
        bool   collided;
        vec3   point;
        vec3   normal;
        object obj;
}

// how muchh config to we really need??? could easily just skip the defocus stuff then its only the samples and bounces
struct config_var {
        int conf;
        int type;   
        // finish this
}

struct camera {
        vec3 pos;
        vec3 plane_00;
        vec3 plane_dx;
        vec3 plane_dy;
}