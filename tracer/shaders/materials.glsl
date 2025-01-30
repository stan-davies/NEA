const int MATT = 77;
const int SHNY = 83;
const int REFL = 82;
const int GLSS = 71;
const int LGHT = 76;

const float PI = 3.1415926535897932384626433832795;

void transmit(in hit_record rec, inout vec3 r) {
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
		transmit_shny(rec, r);
		break;

	default:
		break;
	}
			
}

void transmit_matt(in hit_record rec, inout vec3 r) {
        float theta = dot(rec.normal, r) / (length(rec.normal) * length(r));
	mc_reflect(rec.normal, cos(theta) / PI, r);
}

void transmit_refl(in hit_record rec, inout vec3 r) {
	mc_reflect(rec.normal, 1.0 / (4.0 * PI), r);
}

void transmit_shny(in hit_record rec, inout vec3 r) {
        mc_reflect(rec.normal, 1.0 / (2.0 * PI), r);
}

void transmit_glss(in hit_record rec, inout vec3 r) {
        float ri = rec.interior ? 3.0 / 2.0 : 2.0 / 3.0;

        vec3 unit_dir = normalise(r.dir);
        float cos_theta = min(dot(-unit_dir, rec.normal), 1.0);
        float sin_theta = sqrt(1.0 - cos_theta * cos_theta);

        bool no_refr = ri * sin_theta > 1.0;

        float rnd;
        random_float(r.xy, r);

        float R;
        reflectance(cos_theta, ri, R);

        if (no_refr || R > rnd) {
                transmit_refl(rec, r);
        } else {
                r = refract(r, normal, ri);
        }

        return;
}

void mc_reflect(in vec3 normal, in float fuzz_factor, inout vec3 r) {
        r = reflect(r, normal);
	vec3 offset;
	fuzz_offset(r, fuzz_factor, offset)
	r += offset;
}

void random_float(in vec2 s, out float r) {
	r = abs(fract(sin(dot(s, vec2(12.9898, 78.233))) * 43758.5453));
}

void fuzz_offset(in vec3 reference, in float fuzz_factor, out vec3 offset) {
	bool valid = false;

	vec3 offset;

	float x;
	float y;
	float z;

	while (!valid) {
		random_float(reference.xy, x);
		random_float(reference.yz, y);
		random_float(reference.zx, z);

		offset = normalise(vec3(x, y, z));

		if (dot(offset, reference) <= fuzz_factor) {
			break;
		}
	}
}

void reflectance(in float cosine, in float ri, out float R) {
        float r0 = (1 - ri) / (1 + ri);
        r0 *= r0;
        R = r0 + (1 - r)) * pow(1 - cosine, 5);
}