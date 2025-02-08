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
        r.origin = cam.pos;
        r.dir = curr_px - cam.pos;

        hit_record rec;

        sphere_hit(world[0], r, rec);

        if (rec.collided) {
                pixel = vec4(rec.obj.albedo, 0.0);
        }

        /*
        for (int s = 0; s < max_samples; ++s) {
                ray r;
                r.origin = cam.pos;
                r.dir = (cam.plane_00 + (pixel_coords.x * cam.plane_dx) + (pixel_coords.y * cam.plane_dy)) - r.origin;

                vec3 current_sample;

                for (int b = 0; b < max_bounces; ++b) {
                        bounce(r, current_sample);

                        if (current_sample == vec3(0.0, 0.0, 0.0)) {
                                break;
                        }

                        pixel += vec4(current_sample, 0.0);
                }
        }
        */

        imageStore(img_output, pixel_coords, pixel);
        // imageStore(img_output, pixel_coords, pixel / max_samples);
}

void bounce(inout ray r, out vec3 attenuation) {
        hit_record rec;
        collision(r, rec);

        if (!rec.collided) {
                attenuation = vec3(0.0, 0.0, 0.0);
                return;
        }
	
	// albedo is used for attenuation and it is the amount of light reflected / the colour
	attenuation = rec.obj.albedo; 

	if (rec.obj.mat == LGHT) {
		return;
	}

        r.origin = rec.point;
        transmit(rec, r);
}