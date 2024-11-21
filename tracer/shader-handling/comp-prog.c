#include "comp-prog.h"

int create_comp_program(int *program_id) {
        int shd_id;
        if (!create_shader(&shd_id, SHADER_DIR, GL_COMPUTE_SHADER)) {
                log_err("could not create shader");
                return FALSE;
        }

        int prog_id = glCreateProgram();
        glAttachShader(prog_id, shd_id);
        glLinkProgram(prog_id);

        int link_stat = -1;
        glGetProgramiv(prog_id, GL_LINK_STATUS, &link_stat);
        if (GL_TRUE != link_stat) {
                log_err("could not link shader program '%d'", prog_id);
                log_program_logs(prog_id);
                return FALSE;
        }

        glValidateProgram(prog_id);

        int valid = -1;
        glGetProgramiv(prog_id, GL_VALIDATE_STATUS, &valid);
        if (GL_TRUE != valid) {
                log_err("could not validate shader program '%d'", prog_id);
                log_program_logs(prog_id);
                return FALSE;
        }

        *program_id = prog_id;
        return TRUE;
}

void run_comp_program(int program_id, int groups_x, int groups_y) {
        glUseProgram(program_id);
        glDispatchCompute(groups_x, groups_y, 1);
        glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}