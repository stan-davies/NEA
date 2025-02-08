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

        for (int s = 0; s < max_samples; ++s) {
                r.origin = cam.pos;
                r.dir = curr_px - cam.pos;

                vec3 current_sample;

                for (int b = 0; b < max_bounces; ++b) {
                        bounce(r, current_sample);

                        if (current_sample == vec3(0.0, 0.0, 0.0)) {
                                break;
                        }

                        pixel = pixel + vec4(current_sample, 0.0);
                }
        }

        imageStore(img_output, pixel_coords, pixel / max_samples);
}

void bounce(inout ray r, out vec3 attenuation) {
        hit_record rec;
        collision(r, rec);

        if (!rec.collided) {
                attenuation = vec3(0.0, 0.0, 0.0);
                return;
        }
	
	attenuation = rec.obj.albedo;

	// if (rec.obj.mat == LGHT) {
	// 	return;
	// }

        // r.origin = rec.point;
        // transmit(rec, r);
}