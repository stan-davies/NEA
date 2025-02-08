#define SPHERE 83
#define CUBOID 67
#define PLANE  80

void collision(in ray r, out hit_record rec) {
        bool collided = false;
        hit_record nearest;
        nearest.collided = false;
        hit_record current;

        for (int i = 0; i < obj_c; ++i) {
                hit(world[i], r, current);

                if (false == current.collided) {
                        continue;
                }

                if (distance(r.origin, current.point) < distance(r.origin, nearest.point)) {
                        nearest = current;
                }
        }

        rec = nearest;
        rec.interior = dot(r.dir, rec.normal) >= 0;
}

void hit(in object obj, in ray r, out hit_record rec) {
        switch (obj.type) {
        case SPHERE:
                sphere_hit(obj, r, rec);
                break;
        case PLANE:
                break;
                // plane_hit(obj, r, rec);
        default:
                break;
        }
}

void sphere_hit(in object obj, in ray r, out hit_record rec) {
        vec3 oc = r.origin - obj.coords;

        // a = 1
        float b = 2.0 * dot(oc, normalize(r.dir));
        float c = dot(oc, oc) - (obj.dims.x * obj.dims.x);

        float desc = (b * b) - (4.0 * c);

        rec.collided = (desc >= 0.0);

        if (!rec.collided) {
                return;
        }

        float sr_d = sqrt(desc);
        float t_m = (-b + sr_d) / (2.0);
        float t_p = (-b - sr_d) / (2.0);
        float t = min(t_m, t_p);

        rec.point = r.origin + (t * r.dir);
        rec.normal = (rec.point - obj.coords) / obj.dims.x;
        rec.obj = obj;

        return;
}

// void plane_hit(in object obj, in ray r, out hit_record rec) {
// 	// add second data for the u and v?
// 	vec3 n = normalize(cross(obj.dim1, obj.dim2));

//         float denominator = dot(obj.dims, n);

// 	rec.collided = (abs(denominator) > 0.001);

//         if (!rec.collided) {
//                 return;
//         }

//         float lambda = (D - dot(n, r.origin)) / denominator;

//         vec3 POI = r.origin + (lambda * r.dir);

//         vec3 otp = POI - obj.coords;

// 	float A = dot(POI, obj.dim1);
// 	float B = dot(POI, obj.dim2);

// 	if (A > normalize(obj.dim1) || B > normalize(obj.dim2) || A < 0 || B < 0) {
// 		rec.collided = false;
// 		return;
// 	}

//         rec.point = POI;
//         rec.normal = n;
//         rec.obj = obj;
// }