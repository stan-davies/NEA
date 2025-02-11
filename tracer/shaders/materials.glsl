#define MATT 77
#define SHNY 83
#define REFL 82
#define GLSS 71
#define LGHT 76

#define PI 3.1415926535897932384626433832795

void transmit(in hit_record rec, inout ray r) {
        r.origin = rec.point;
        
	switch (rec.obj.mat) {
	case MATT:
		transmit_matt(rec, r);
		break;
	case SHNY:
		transmit_shny(rec, r);
		break;
	case REFL:
		transmit_refl(rec, r);
		break;
	case GLSS:
		transmit_glss(rec, r);
		break;
	default:
		break;
	}

        r.dir = normalize(r.dir);
			
}

void transmit_matt(in hit_record rec, inout ray r) {
        vec3 rnd_unit;
        float theta = dot(rec.normal, r.dir) / (length(rec.normal) * length(r.dir));
        vec3 mc_smp = rec.point * cos(theta) / PI;
        random_unit(mc_smp, rnd_unit);

        r.dir = rec.normal + rnd_unit;

        vec3 abs_dir = abs(r.dir);
        if (abs_dir.x < 1e-4 && abs_dir.y < 1e-4 && abs_dir.z < 1e-4) {
                r.dir = rec.normal;
        }
}

void transmit_refl(in hit_record rec, inout ray r) {
        r.dir = reflect(r.dir, rec.normal);
}

void transmit_shny(in hit_record rec, inout ray r) {
        vec3 rnd_unit;
        float theta = dot(rec.normal, r.dir) / (length(rec.normal) * length(r.dir));
        vec3 mc_smp = rec.point * cos(theta) / PI;
        random_unit(rec.point, rnd_unit);

        float fuzz_factor;
        random_float(rec.normal.xy, fuzz_factor);

        r.dir = reflect(r.dir, rec.normal);
        r.dir = normalize(r.dir) + (PI * fuzz_factor * rnd_unit);

        if (dot(r.dir, rec.normal) <= 0) {
                r.dir *= -1;
        }
}

void transmit_glss(in hit_record rec, inout ray r) {
        float ri = 3.0 / 2.0;
        if (rec.interior) {
                ri = 1.0 / ri;
        }

        float cos_theta = min(dot(-r.dir, rec.normal), 1.0);
        float sin_theta = sqrt(1.0 - (cos_theta * cos_theta));

        bool no_refr = ri * sin_theta > 1.0;

        float rnd;
        random_float(rec.point.xy, rnd);

        float R;
        reflectance(cos_theta, ri, R);

        if (no_refr || R > rnd) {
                transmit_refl(rec, r);
        } else {
                // r.dir = refract(r.dir, rec.normal, ri);
                vec3 r_out_perp = ri * (r.dir + cos_theta * rec.normal);
                float perp_len = dot(r_out_perp, r_out_perp);
                vec3 r_out_para = -sqrt(abs(1.0 - perp_len * perp_len)) * rec.normal;
                r.dir = r_out_perp + r_out_para;
        }
}

void random_float(in vec2 s, out float r) {
	r = abs(fract(sin(dot(s, vec2(12.9898, 78.233))) * 43758.5453));
}

void random_unit(in vec3 s, out vec3 v) {
        float x, y, z;
        float len_sq;
        while (true) {
                random_float(s.xy, x);
                // Transform [0, 1] to [-1, 1]
                x = (x * 2.0) - 1.0;
                random_float(s.yz, y);
                y = (y * 2.0) - 1.0;
                random_float(s.zx, z);
                z = (z * 2.0) - 1.0;
                len_sq = (x * x) + (y * y) + (z * z);
                if (len_sq > 1e-80) {
                        break;
                }
        }

        v = vec3(x, y, z) / sqrt(len_sq);
}

void reflectance(in float cosine, in float ri, out float R) {
        float r0 = (1 - ri) / (1 + ri);
        r0 *= r0;
        R = r0 + (1 - r0) * pow(1 - cosine, 5);
}