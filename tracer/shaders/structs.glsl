struct ray {
        vec3 origin;
        vec3 dir;
};

struct object {
        int  type;
        vec3 coords;
        vec3 dims;
        int  mat;
        vec3 albedo;
};

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