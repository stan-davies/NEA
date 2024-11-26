#version 460

layout(local_size_x = 1, local_size_y = 1) in;
// this is how it is linked, this is setting it to be GL_TEXTURE0
layout(binding = 0, rgba32f) writeonly uniform image2D img_output;

void main() {
        ivec2 pixel_coords = ivec2(gl_GlobalInvocationID.xy);

        vec4 pixel = vec4(0.3, 0.6, 0.2, 0.0);

        imageStore(img_output, pixel_coords, pixel);
}