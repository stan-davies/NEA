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
        // Used with glass to determine the current ratio of indices of refraction.
        //rec.interior = dot(r.dir, rec.normal) >= 0;
}

void hit(in object obj, in ray r, in float low, out hit_record rec) {
        switch (obj.type) {
        case SPHERE:
                sphere_hit(obj, r, low, rec);
                break;
        case PLANE:
                plane_hit(obj, r, low, rec);
                break;
        default:
                break;
        }
}

void sphere_hit(in object obj, in ray r, in float low, out hit_record rec) {
        vec3 oc = obj.coords - r.origin;

        float a = dot(r.dir, r.dir);
        float h = dot(oc, (r.dir));
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
                        return;
                }
        }

        rec.point = r.origin + (t * r.dir);
        rec.normal = normalize((rec.point - obj.coords) / obj.dims.x);
        if (dot(r.dir, rec.normal) > 0) {
                // ray is coming from inside sphere
                rec.interior = true;
                rec.normal *= -1;
        } else {
                // ray is coming from outside sphere
                rec.interior = false;
        }
        rec.obj = obj;
}

void plane_hit(in object obj, in ray r, in float low, out hit_record rec) {
        vec3 n = normalize(obj.dims);
        float denominator = dot(n, r.dir);

	rec.collided = abs(denominator) > 1e-8;

        if (!rec.collided) {
                return;
        }

        float t = (obj.coords.x - dot(n, r.origin)) / denominator;

        if (t <= low) {
                rec.collided = false;
                return;
        }

        vec3 POI = r.origin + (t * r.dir);

        rec.point = POI;
        rec.normal = n;
        rec.obj = obj;
}