#include "shad-parser.h"

int preprocess(char *dir_path, char **shader_string) {
        char *cnt;
        int cnt_len;

        if (!get_file_cnt(dir_path, "main", &cnt, &cnt_len)) {
                log_err("cannot find main shader file");
                return FALSE;
        }

        if (!direct(dir_path, &cnt, &cnt_len)) {
                log_err("coult not fulfil directives");
                return FALSE;
        }

        *shader_string = cnt;
}

int get_file_cnt(char *dir_path, char *name, char **cnt, int *cnt_len) {
        char *path;
        sprintf(path, "%s%s.glsl", dir_path, name);
        return parse(path, cnt, cnt_len);
}

int direct(char *dir_path, char **content, int *content_len) {
        char *parsed = calloc(MAX_SHADER_LENGTH, sizeof(char));
        int parsed_len = 0;

        char current_chr;

        int line_count = 0;
        int directive = FALSE;
        int filename = FALSE;

        char* filename_str = calloc(MAX_FILENAME_LEN, sizeof(char));
        int filename_cc = 0;

        for (int i = 0; i < *content_len; ++i) {
                line_count++;

                current_chr = (*content)[i];

                // potentially do a 'status' with *(directive or filename) << 3 + current_chr or something

                if (0 == line_count && HASH_CHR == current_chr) {
                        directive = TRUE;
                } else if (QUT_CHR) {
                        if (directive) {
                                directive = FALSE;
                                filename = TRUE;
                        }

                        if (filename) {
                                filename = FALSE;

                                char *cnt;
                                int cnt_len;

                                if (!get_file_cnt(dir_path, filename_str, &cnt, &cnt_len)) {
                                        log_err("file at '%s%s.glsl' could not be found", dir_path,  filename_str);
                                        return FALSE;
                                }

                                if (!direct(dir_path, &cnt, &cnt_len)) {
                                        log_err("could not fulfil directives for '%s%s.glsl'", dir_path, filename_str);
                                        return FALSE;
                                }

                                sprtinf(parsed, "%s%s", parsed, cnt);
                                parsed_len += cnt_len;

                        }
                } else if (filename) {
                        filename_str[filename_cc] = current_chr;
                        filename_cc++;
                } else {
                        parsed[parsed_len] = current_chr;
                        parsed_len++;
                }
        }

        free(content);
        content = parsed;

        free(filename_str);

        return TRUE;
}

int create_shader(int *shader_id, char *dir_path, GLenum type) {
        char *shd_str = (char *)malloc(MAX_SHADER_LENGTH * sizeof(char));
        if (!preprocess(dir_path, &shd_str)) {
                log_err("could not preprocess shaders at '%s'", dir_path);
                return FALSE;
        }

        GLuint tmp_shd_id = glCreateShader(type);
        glShaderSource(tmp_shd_id, 1, (const GLchar **)shd_str, NULL);
        glCompileShader(tmp_shd_id);

        free(shd_str);
        shd_str = NULL;

        int sh_cmp_stat = -1;
        glGetShaderiv(tmp_shd_id, GL_COMPILE_STATUS, &sh_cmp_stat);
        if (GL_TRUE != sh_cmp_stat) {
                log_err("shaders at '%s' could not be compiled", dir_path);
                return FALSE;
        }

        *shader_id = tmp_shd_id;
        return TRUE;
}