const int SPHERE 83;
const int CUBOID 67;
const int PLANE  80;

struct hit_record collision(object world[MAX_OBJ_COUNT], int obj_c, ray r) {
        bool collided = false;
        struct hit_record nearest;
        nearest.collided = false;
        struct hit_record current;

        for (int i = 0; i < obj_c; ++i) {
                current = hit(world[i], r);

                if (false == current.collided) {
                        continue;
                }

                if (distance(r.origin, current.point) < distance(r.origin, nearest.point)) {
                        nearest = current;
                }
        }

        return nearest;
}

bool hit(struct object obj, struct ray r) {
        switch (obj.type) {
        case SPHERE:
                return sphere_hit(obj, r);
        // case CUBOID:
        //         return cuboid_hit(obj, r, rec);
        // case PLANE:
        //         return plane_hit(obj, r, rec);
        default:
                return rec;
        }
}

// sphere requires a vec3 centre and a float radius
/*
 * vec3  :  coords
 * float :  radius
 *
 * 4 floats total
 */
struct hit_record sphere_hit(struct object obj, struct ray r) {
        struct hit_record rec;

        vec2 oc = r.origin - obj.coords;

        // a = 1
        float b = 2.0 * dot(oc, unit(r.dir));
        float c = dot(oc, oc) - (obj.dims.x * obj.dims.x);

        float desc = (b * b) - (4.0 * c);

        rec.collided = (desc < 0.0);

        if (!rec.collided) {
                return rec;
        }

        float sr_d = sqrt(desc);
        float t_m = (-b + sr_d) / (2.0 * a);
        float t_p = (-b - sr_d) / (2.0 * a);
        float t = min(t_m, t_p);

        rec.point = r.origin + (t * r.dir);
        rec.normal = (rec.point - obj.coords) / obj.dims.x;
        rec.obj = obj;

        return rec;
}

// commented:

// // a cube requires a vec3 for the corner, three vec3's for u, v, and w, and three floats for alpha, beta and gamma
// /*
//  * vec3  :  coords
//  * vec3  :  u
//  * vec3  :  v
//  * vec3  :  w
//  * vec3  :  α β γ
//  *
//  * 15 floats total
//  */
// struct hit_record cube_hit(struct object obj, struct ray r, struct hit_record rec) {
//         // given a point

        
// }

// // plane should have two perpendicular vectors, then the normal would be taken as the unit vector of the cross product of these two
// // then we would also need two floats, a & b, which scale these two vectors to see how big the plane can be

// // a plane requires a vec3 for the corner, two vec3's for u and v, and two floats for alpha and beta
// /*
//  * vec3  :  coords
//  * vec3  :  u
//  * vec3  :  v
//  * vec2  :  α β
//  *
//  * 11 floats total
//  */
// struct hit_record plane_hit(struct object obj, struct ray r, struct hit_record rec) {
//         // in this case, the dimensions will be taken as the normal to the plane
//         float denominator = dot(obj.dims, r.dir);

//         if (0 == denominator) {   // could replace with (abs(denominator) < SOME_SMALL_VALUE)
//                 return false;
//         }

//         float lambda = (D - dot(obj.dims, r.origin)) / denominator;

//         vec3 POI = r.origin + (lambda * r.dir);

//         vec3 otp = POI - obj.coords;

//         // separate otp into components parallel to u and v and then if the magnitudes are less than a & b

//         rec.point = POI;
//         rec.normal = obj.dims;
//         rec.obj = obj;
// }

// struct hit_record OBJECT_hit(struct object obj, struct ray r, struct hit_record rec) {
//         // if not hit
//                 // return false

//         // update record
//         // return that
// }