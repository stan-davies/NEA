#include "comp-prog.h"

int create_comp_program(int *program_id) {
        int shd_id;
        if (!create_shader(&shd_id, SHADER_DIR, GL_COMPUTE_SHADER)) {
                log_err("Could not create shader.");
                return FALSE;
        }

        int prog_id = glCreateProgram();
        glAttachShader(prog_id, shd_id);
        glLinkProgram(prog_id);

        int link_stat = -1;
        glGetProgramiv(prog_id, GL_LINK_STATUS, &link_stat);
        if (GL_TRUE != link_stat) {
                log_err("Could not link shader program '%d'.", prog_id);
                log_program_logs(prog_id);
                log_shader_logs(shd_id);
                return FALSE;
        }

        glValidateProgram(prog_id);

        int valid = -1;
        glGetProgramiv(prog_id, GL_VALIDATE_STATUS, &valid);
        if (GL_TRUE != valid) {
                log_err("Could not validate shader program '%d'.", prog_id);
                log_program_logs(prog_id);
                log_shader_logs(shd_id);
                return FALSE;
        }

        *program_id = prog_id;
        return TRUE;
}

void run_comp_program(int program_id, int groups_x, int groups_y) {
        glUseProgram(program_id);
        glDispatchCompute(groups_x, groups_y, 1);
        glMemoryBarrier(GL_TEXTURE_UPDATE_BARRIER_BIT);
}