#version 460

#include "structs"

layout(local_size_x = 1, local_size_y = 1) in;
layout(binding = 0, rgba32f) writeonly uniform image2D img_output;
uniform object world[MAX_OBJ_COUNT];
uniform int obj_c;
uniform camera cam;
uniform int max_bounces;
uniform int max_samples;
uniform float ambient_coef;

#include "prototype"
#include "materials"
#include "objects"

void main() {
        ivec2 pixel_coords = ivec2(gl_GlobalInvocationID.xy);
        ivec2 work_groups = ivec2(gl_NumWorkGroups.xy);
        vec4 pixel = vec4(0.0, 0.0, 0.0, 0.0);
        vec3 curr_px = cam.plane_00 + (pixel_coords.x * cam.plane_dx) + (pixel_coords.y * cam.plane_dy);
        ray r;
        vec3 current_sample;
        bool brk;
        bool lit;

        for (int s = 0; s < max_samples; ++s) {
                make_ray(ivec3(work_groups, s), cam, pixel_coords, r);

                current_sample = vec3(1.0, 1.0, 1.0);

                brk = false;
                lit = false;

                for (int b = 0; b < max_bounces; ++b) {
                        bounce(r, current_sample, brk, lit);

                        if (brk) {
                                break;
                        } else if (b == max_bounces - 1 && max_bounces > 1) {
                                current_sample = vec3(0.0, 0.0, 0.0);
                        }
                }

                if (lit) {
                        pixel += vec4(current_sample, 0.0);
                } else {
                        pixel += vec4(current_sample * ambient_coef, 0.0);
                }
        }

        imageStore(img_output, pixel_coords, pixel / float(max_samples));
}

void bounce(inout ray r, inout vec3 attenuation, out bool brk, out bool lit) {
        hit_record rec;
        collision(r, 0.0001, rec);

        if (!rec.collided) {
                float a = 0.5 * (r.dir.y + 1.0);
                attenuation *= ((1.0 - a) * vec3(1.0, 1.0, 1.0)) + (a * vec3(0.5, 0.7, 1.0));

                brk = true;
                lit = false;
                return;
        }

        transmit(rec, r);

        if (!rec.collided) {
                attenuation = vec3(0.0, 0.0, 0.0);
                brk = true;
                lit = false;
                return;
        }

        attenuation *= rec.obj.albedo;

	if (rec.obj.mat == LGHT) {
                brk = true;
                lit = true;
		return;
	}

        brk = false;
        lit = false;
}

void make_ray(in ivec3 smp, in camera c, in ivec2 px, inout ray r) {
        float offs_x;
        float offs_y;

        random_float(vec2(smp.z, smp.y), offs_x);
        offs_x -= 0.5;
        random_float(vec2(smp.x, smp.z), offs_y);
        offs_y -= 0.5;

        r.origin = c.pos;
        r.dir = normalize(c.plane_00 + ((px.x + offs_x) * c.plane_dx) + ((px.y + offs_y) * c.plane_dy) - c.pos);
}