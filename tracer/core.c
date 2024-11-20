#include "core.h"

int render() {
        GLint shader_id;

        if (!create_shader(&shader_id, "tracer/shaders/", GL_COMPUTE_SHADER)) {
                log_err("failed to create shader");
                return FALSE;
        }

        return TRUE;
}