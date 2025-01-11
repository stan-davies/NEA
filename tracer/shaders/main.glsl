#version 460

#include "structs"

layout(local_size_x = 1, local_size_y = 1) in;
layout(binding = 0, rgba32f) writeonly uniform image2D img_output;
// 128 is max object count
layout(location = 0) uniform object world[128];
// world takes up 512 uniform locations due to it being 128 instances of a 4 variable struct
layout(location = 512) uniform int obj_c;
layout(location = 513) uniform camera cam;
layout(location = 514) uniform int max_bounces;
layout(location = 515) uniform int max_samples;

#include "prototype"
#include "objects"

void main() {
        ivec2 pixel_coords = ivec2(gl_GlobalInvocationID.xy);
        ivec2 work_groups = ivec2(gl_NumWorkGroups.xy);
        vec4 pixel = vec4(0.0, 0.0, 0.0, 0.0);

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

        imageStore(img_output, pixel_coords, pixel / max_samples);
}

void bounce(inout ray r, out vec3 attenuation) {
        hit_record rec;
        collision(r, rec);

        if (!rec.collided) {
                attenuation = vec3(0.0, 0.0, 0.0);
                return;
        }

        r.origin = rec.point;
        r.dir = vec3(0.0, 0.0, 0.0);// the reflected path, which is calculated using the material and the surface normal and some probability magic

        // albedo is used for attenuation and it is the amount of light reflected / the colour
        // do something fancy here with getting the right colour or something
        attenuation = rec.obj.albedo; 
}