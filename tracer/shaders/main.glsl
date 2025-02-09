#version 460

#include "structs"

layout(local_size_x = 1, local_size_y = 1) in;
layout(binding = 0, rgba32f) writeonly uniform image2D img_output;
uniform object world[MAX_OBJ_COUNT];
uniform int obj_c;
uniform camera cam;
uniform int max_bounces;
uniform int max_samples;
uniform bool do_light;

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
        float offs_x;
        float offs_y;
        bool brk;
        bool lit;

        for (int s = 0; s < max_samples; ++s) {
                random_float(vec2(s, work_groups.y), offs_x);
                offs_x -= 0.5;
                random_float(vec2(work_groups.x, s), offs_y);
                offs_y -= 0.5;

                r.origin = cam.pos;
                r.dir = cam.plane_00 + ((pixel_coords.x + offs_x) * cam.plane_dx) + ((pixel_coords.y + offs_y) * cam.plane_dy) - cam.pos;

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

                if (lit || !do_light) {
                        pixel += vec4(current_sample, 0.0);
                } else {
                       pixel += vec4(current_sample * 0.01, 0.0);
                }
        }

        imageStore(img_output, pixel_coords, pixel / float(max_samples));
}

void bounce(inout ray r, inout vec3 attenuation, out bool brk, out bool lit) {
        hit_record rec;
        collision(r, 0.0001, rec);

        if (!rec.collided) {
                float a = 0.5 * (normalize(r.dir).y + 1.0);
                attenuation *= ((1.0 - a) * vec3(1.0, 1.0, 1.0)) + (a * vec3(0.5, 0.7, 1.0));
                brk = true;
                lit = false;
                return;
        }

        attenuation *= rec.obj.albedo;

	if (rec.obj.mat == LGHT && do_light) {
                brk = true;
                lit = true;
		return;
	}

        transmit(rec, r);
        brk = false;
        lit = false;
}