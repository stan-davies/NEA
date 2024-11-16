#include "gl-init.h"

int window_width  = 1;
int window_height = 1; 

int init_gl(enum PROGS type, GLFWwindow *window) {
        glfwSetErrorCallback(glfw_error_callback);

        if (!glfwInit()) {
                log_err("failed to initialise glfw");
                return FALSE;
        }

        // set opengl to use version 4.6 core
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 6 );
        glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
        glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

        if (EDIT == type) {
                glfwWindowHint(GLFW_SAMPLES, 4);
        }

        // hides the created window, this is because a rendering context is required for OpenGL,
        // but no rendering will be done and we don't even really want a window, we are just using
        // OpenGL to interface with the GPU
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

        window = glfwCreateWindow(1, 1, "tracer", NULL, NULL);
        
        if (NULL == window) {
                log_err("failed to create window with type %d", type);
                glfwTerminate();
                return FALSE;
        }

        // set window to the current context, required for initialisation
        glfwMakeContextCurrent(window);

        if (EDIT == type) {
                glfwSetFramebufferSizeCallback(window, glfw_window_resize_callback);
        }

        glewInit();

        log_gl_vars();
}

void term_gl() {
        glfwTerminate();
}

void glfw_error_callback(int error, const char *description) {
        log_err(description);
}

void glfw_window_resize_callback(GLFWwindow *window, int w, int h) {
        window_width  = w;
        window_height = h;

        // update perspective matrices if necessary
}

void log_gl_vars() {
        GLubyte *gl_version = glGetString(GL_VERSION);
        GLubyte *gl_vendor = glGetString(GL_VENDOR);
        GLubyte *glsl_version = glGetString(GL_SHADING_LANGUAGE_VERSION);

        log("\topengl version : %s", (char *)gl_version);
        log("\topengl implementation vendor : %s", (char *)gl_vendor);
        log("\tglsl version : %s", (char *)glsl_version);
}