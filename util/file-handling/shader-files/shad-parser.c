#include "shad-parser.h"

int preprocess(char *dir_path, char **shader_string) {
        char *cnt;
        int cnt_len;

        if (!get_file_cnt(dir_path, "main", &cnt, &cnt_len)) {
                log_err("cannot find main shader file");
                return FALSE;
        }

        if (!direct(dir_path, &cnt, cnt_len)) {
                log_err("coult not fulfil directives");
                return FALSE;
        }

        *shader_string = cnt;
        
        return TRUE;
}

int get_file_cnt(char *dir_path, char *name, char **cnt, int *cnt_len) {
        char *path = calloc(MAX_PATH_LENGTH, sizeof(char));
        sprintf(path, "%s%s.glsl", dir_path, name);
        return parse(path, cnt, cnt_len);
}

int direct(char *dir_path, char **content, int content_len) {
        char *parsed = calloc(MAX_FILE_LENGTH, sizeof(char));
        int parsed_len = 0;

        char current_chr;

        int line_count = 0;
        int directive = FALSE;
        int filename = FALSE;

        char* filename_str = calloc(MAX_FILENAME_LENGTH, sizeof(char));
        int filename_cc = 0;

        for (int i = 0; i < content_len; ++i) {
                current_chr = (*content)[i];

                if (0 == line_count && HSH_C == current_chr) {
                        if (i == content_len - 1) {
                                goto incomplete_directive;
                        }

                        directive = (I_C == (*content)[i + 1]);
                } else if (QUT_C == current_chr) {
                        if (directive) {
                                directive = FALSE;
                                filename = TRUE;

                                continue;
                        } else if (filename) {
                                filename = FALSE;

                                char *cnt;
                                int cnt_len;

                                if (!get_file_cnt(dir_path, filename_str, &cnt, &cnt_len)) {
                                        log_err("file at '%s%s.glsl' could not be found", dir_path,  filename_str);

                                        goto error;
                                }

                                if (!direct(dir_path, &cnt, cnt_len)) {
                                        log_err("could not fulfil directives for '%s%s.glsl'", dir_path, filename_str);
                                        
                                        goto error;
                                }

                                sprintf(parsed, "%s%s", parsed, cnt);
                                parsed_len += cnt_len;

                                continue;

                        }
                } 
                
                if (filename) {
                        filename_str[filename_cc] = current_chr;
                        filename_cc++;
                } else if (!directive) {
                        parsed[parsed_len] = current_chr;
                        parsed_len++;

                        line_count++;
                }

                if (LF_C == current_chr) {
                        if (directive || filename) {
                                goto incomplete_directive;
                        }

                        line_count = 0;
                } 
        }

        free(*content);
        *content = parsed;

        free(filename_str);
        filename_str = NULL;

        if (directive || filename) {
                goto incomplete_directive;
        }

        return TRUE;

        incomplete_directive:
        log_err("incomplete directive in file '%s.glsl'", dir_path);

        error:
        if (*content != parsed) {
                free(*content);
        }
        free(parsed);
        free(filename_str);

        return FALSE;
}

int create_shader(int *shader_id, char *dir_path, GLenum type) {
        char *shd_str = (char *)malloc(MAX_FILE_LENGTH * sizeof(char));
        if (!preprocess(dir_path, &shd_str)) {
                free(shd_str);
                log_err("could not preprocess shaders at '%s'", dir_path);
                return FALSE;
        }

        GLuint tmp_shd_id = glCreateShader(type);
        glShaderSource(tmp_shd_id, 1, &shd_str, NULL);
        glCompileShader(tmp_shd_id);

        free(shd_str);
        shd_str = NULL;

        int shd_cmp_stat = -1;
        glGetShaderiv(tmp_shd_id, GL_COMPILE_STATUS, &shd_cmp_stat);
        if (GL_TRUE != shd_cmp_stat) {
                log_err("shaders at '%s' could not be compiled", dir_path);
                log_shader_logs(tmp_shd_id);
                return FALSE;
        }

        *shader_id = tmp_shd_id;
        return TRUE;
}