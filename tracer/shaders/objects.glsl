const int SPHERE 83;
const int CUBOID 67;
const int PLANE  80;

struct object {
        int  type;
        vec3 coords;
        vec3 dims;
        int  mat;
}

struct hit_record {
        vec3   point;
        vec3   normal;
        struct object obj;
}

bool hit(struct object obj, struct ray r, struct hit_record rec) {
        switch (obj.type) {
        case SPHERE:
                return sphere_hit(obj, r, rec);
        case CUBOID:
                return cuboid_hit(obj, r, rec);
        case PLANE:
                return plane_hit(obj, r, rec);
        default:
                return false;
        }
}

bool sphere_hit(struct object obj, struct ray r, struct hit_record rec) {
        vec2 oc = r.origin - obj.dims.x;

        float a = 1;
        float b = 2.0 * dot(oc, unit(r.dir));
        float c = dot(oc, oc) - (obj.dims.x * obj.dims.x);

        float desc = (b * b) - (4.0 * a * c);

        if (desc < 0) {
                return false;
        }

        return true;
}

bool cube_hit(struct object obj, struct ray r, struct hit_record rec) {
        // given a point

        
}

float pow100(float n) {
        float res = 1;

        for (int i = 0; i < 100; ++i) {
                res *= n;
        }

        return res;
}

// plane should have two perpendicular vectors, then the normal would be taken as the unit vector of the cross product of these two
// then we would also need two floats, a & b, which scale these two vectors to see how big the plane can be
bool plane_hit(struct object obj, struct ray r, struct hit_record rec) {
        // in this case, the dimensions will be taken as the normal to the plane
        float denominator = dot(obj.dims, r.dir);

        if (0 == denominator) {   // could replace with (abs(denominator) < SOME_SMALL_VALUE)
                return false;
        }

        float lambda = (D - dot(obj.dims, r.origin)) / denominator;

        vec3 POI = r.origin + (lambda * r.dir);

        vec3 otp = POI - obj.coords;

        // separate otp into components parallel to u and v and then if the magnitudes are less than a & b

        rec.point = POI;
        rec.normal = obj.dims;
        rec.obj = obj;
}

bool OBJECT_hit(struct object obj, struct ray r, struct hit_record rec) {
        // if not hit
                // return false

        // update record
        // return true
}