#version 460

layout(local_size_x = 1, local_size_y = 1) in;
// this is how it is linked, this is setting it to be GL_TEXTURE0
layout(binding = 0, rgba32f) writeonly uniform image2D img_output;

layout(location = 0) uniform object[MAX_OBJ_COUNT] world;
// world takes up 512 uniform locations due to it being 128 instances of a 4 variable struct
layout(location = 512) uniform int obj_c;
layout(location = 513) uniform camera cam;
layout(location = 514) uniform int max_bounces;
layout(location = 515) uniform int max_samples;

#include "structs.glsl"
#include "globals.glsl"
#include "objects.glsl"

void main() {
        ivec2 pixel_coords = ivec2(gl_GlobalInvocationID.xy);
        ivec2 work_groups = ivec2(gl_NumWorkGroups.xy);
        vec4 pixel = vec4(0.0, 0.0, 0.0, 0.0);

        for (int i = 0; i < MAX_SAMPLES; ++i) {
                ray r;
                r.origin = cam.coords;
                r.dir = (cam.plane_00 + (pixel_coords.x * cam.plane_dx) + (pixel_coords.y * cam.plane_dy)) - r.origin;

                pixel += vec4(bounce(r, MAX_BOUNCES), 0.0);
        }

        imageStore(img_output, pixel_coords, pixel / MAX_SAMPLES);
}

vec3 bounce(ray r, int depth) {
        if (depth <= 0) {
                return vec3(0.0, 0.0, 0.0);
        }

        hit_record rec = collision(world, obj_c, r);
        if (!rec.collided) {
                return vec3(0.0, 0.0, 0.0)
        }

        r.origin = rec.point;
        r.dir = // the reflected path, which is calculated using the material and the surface normal and some probability magic

        // albedo is used for attenuation and it is the amount of light reflected / the colour
        return rec.obj.albedo * bounce(r, depth - 1); 
}