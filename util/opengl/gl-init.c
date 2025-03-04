#include "gl-init.h"

int init_gl(enum PROGS type, GLFWwindow *window) {
        glfwSetErrorCallback(glfw_error_callback);

        if (!glfwInit()) {
                log_err("Failed to initialise glfw.");
                return FALSE;
        }

        // set opengl to use version 4.6 core
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Hides the created window, this is because a rendering context is required for OpenGL,
        // but no rendering will be done and we don't even really want a window, we are just using
        // OpenGL to interface with the GPU
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

        window = glfwCreateWindow(1, 1, "tracer", NULL, NULL);
        
        if (NULL == window) {
                log_err("Failed to create window with type %d.", type);
                glfwTerminate();
                return FALSE;
        }

        // set window to the current context, required for initialisation
        glfwMakeContextCurrent(window);

        glewInit();

        log_gl_vars();
}

void term_gl() {
        glfwTerminate();
}

void glfw_error_callback(int error, const char *description) {
        log_err(description);
}

void log_gl_vars() {
        GLubyte *gl_version = glGetString(GL_VERSION);
        GLubyte *gl_vendor = glGetString(GL_VENDOR);
        GLubyte *glsl_version = glGetString(GL_SHADING_LANGUAGE_VERSION);

        GLint max_uniforms;
        glGetIntegerv(GL_MAX_COMPUTE_UNIFORM_BLOCKS, &max_uniforms);

        log("\tOpenGL version : %s", (char *)gl_version);
        log("\tOpenGL implementation vendor : %s", (char *)gl_vendor);
        log("\tGLSL version : %s", (char *)glsl_version);
        log("\tMax uniforms for compute shader : %d", max_uniforms);
}