#define SPHERE 83
#define CUBOID 67
#define PLANE  80

void collision(in ray r, in float low, out hit_record rec) {
        hit_record nearest;
        nearest.collided = false;
        hit_record current;

        int misses = 0;

        for (int i = 0; i < obj_c; ++i) {
                hit(world[i], r, low, current);

                // if (rec.interior) {
                //         nearest = current;
                //         break;
                // }

                if (!current.collided) {
                        misses++;
                        continue;
                }

                // (!nearest.collided) indicates that this is the first collision
                if (!nearest.collided || distance(r.origin, current.point) < distance(r.origin, nearest.point)) {
                        nearest = current;
                }
        }

        if (misses == obj_c) {
                rec.collided = false;
                return;
        }

        rec = nearest;
        // rec.interior = dot(r.dir, rec.normal) >= 0;
}

void hit(in object obj, in ray r, in float low, out hit_record rec) {
        switch (obj.type) {
        case SPHERE:
                sphere_hit(obj, r, low, rec);
                break;
        case PLANE:
                break;
                // plane_hit(obj, r, low, rec);
        default:
                break;
        }
}

void sphere_hit(in object obj, in ray r, in float low, out hit_record rec) {
        //vec3 oc = r.origin - obj.coords;
        vec3 oc = obj.coords - r.origin;

        float a = dot(r.dir, r.dir);  // =1
        float h = dot(oc, (r.dir));  // -2 *
        float c = dot(oc, oc) - (obj.dims.x * obj.dims.x);

        float desc = (h * h) - (a * c);

        rec.collided = (desc >= 0.0);

        if (!rec.collided) {
                return;
        }

        float sr_d = sqrt(desc);
        float t_m = (h + sr_d) / a;
        float t_p = (h - sr_d) / a;
        float t = min(t_m, t_p);

        if (t <= low) {
                t = max(t_m, t_p);
                if (t <= low) {
                        rec.collided = false;
                        rec.interior = true;
                        return;
                }
        }

        rec.interior = false;

        rec.point = r.origin + (t * r.dir);
        rec.normal = normalize((rec.point - obj.coords) / obj.dims.x);
        rec.obj = obj;
}

// void plane_hit(in object obj, in ray r, in float low, out hit_record rec) {
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