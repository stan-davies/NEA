#version 460

#include "structs"

layout(local_size_x = 1, local_size_y = 1) in;
layout(binding = 0, rgba32f) writeonly uniform image2D img_output;
uniform object world[MAX_OBJ_COUNT];
uniform int obj_c;
uniform camera cam;
uniform int max_bounces;
uniform int max_samples;

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

        for (int s = 0; s < max_samples; ++s) {
                r.origin = cam.pos;
                r.dir = curr_px - cam.pos;

                current_sample = vec3(0.0, 0.0, 0.0);

                for (int b = 0; b < max_bounces; ++b) {
                        random_float(vec2(s, b), offs_x);
                        offs_x -= 0.5;
                        random_float(vec2(b, s), offs_y);
                        offs_y -= 0.5;

                        r.dir = cam.plane_00 + ((pixel_coords.x + offs_x) * cam.plane_dx) + ((pixel_coords.y + offs_y) * cam.plane_dy) - cam.pos;

                        bounce(r, current_sample);

                        if (current_sample == vec3(0.0, 0.0, 0.0)) {
                                break;
                        }
                }
                pixel += vec4(current_sample, 0.0);
        }

        imageStore(img_output, pixel_coords, pixel / float(max_samples * max_bounces));
}

void bounce(inout ray r, inout vec3 attenuation) {
        hit_record rec;
        collision(r, rec);

        if (!rec.collided) {
                attenuation = vec3(0.0, 0.0, 0.0);
                return;
        }
	
        attenuation = 0.5 * (normalize(rec.normal) + vec3(1.0, 1.0, 1.0));

        // if (attenuation == vec3(0.0, 0.0, 0.0)) {
        //         attenuation = rec.obj.albedo;
        // } else {
        //         attenuation += rec.obj.albedo;
        // }

        // how is this "stop bouncing now" going to filter through??
        // something about if the last collision isnt a light then get mad??
	// if (rec.obj.mat == LGHT) {
	// 	return;
	// }

        r.origin = rec.point;
        transmit(rec, r);
}