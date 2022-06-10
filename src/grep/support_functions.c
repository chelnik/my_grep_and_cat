#include "s21_grep.h"

void template_files_opener(const char **template_files, int num_template_files,
                           const char **template, int *num_template,
                           flags flags, char **str_array) {
    // char str_array[100][256];
    int num_str_array = 0;
    for (int j = 0; j < num_template_files; j++) {
        FILE *file;

        if ((file = fopen(template_files[j], "r")) == NULL) {
            if (!flags.s) {
                fprintf(stderr, "grep: %s: No such file or directory\n",
                        template_files[j]);
                fclose(stderr);
            }
        } else {
            char ch = (char)fgetc(file);

            while (ch != EOF && num_str_array < 98) {
                int i = 0;

                while (ch != '\n' && ch != EOF && i < 254) {
                    str_array[num_str_array][i] = ch;
                    ch = (char)fgetc(file);
                    i++;
                }

                str_array[num_str_array][i] = '\0';
                template[(*num_template)++] = str_array[num_str_array++];
                ch = (char)fgetc(file);
            }
            fclose(file);
        }
    }
}

void cheker_flags_ef(int argc, char const *argv[], flags *flags) {
    for (int i = 0; i < argc; i++) {
        if (argv[i][0] == '-' && (argv[i][1] == 'e' || argv[i][1] == 'f')) {
            flags->there_are_ef_flags = 1;
        }
    }
}

void enter_flager(int *enter_flag, char *buf, flags flags) {
    if (buf[strlen(buf) - 1] == EOF || buf[strlen(buf) - 1] != '\n') {
        if (flags.c == 0 && flags.l == 0) *enter_flag = 1;
    }
}

void function_for_flag_l(int m, const char **files, int num_files, flags flags) {
    if (num_files > 1) {
        if (flags.c) {
            if (flags.h) {
                printf("1\n%s\n", files[m]);
            } else {
                printf("%s:1\n%s\n", files[m], files[m]);
            }
        } else {
            printf("%s\n", files[m]);
        }
    } else {
        if (flags.c) {
            printf("1\n%s\n", files[m]);
        } else {
            printf("%s\n", files[m]);
        }
    }
}

void function_for_flag_o(int num, const char **template, int str_index, int m,
                         const char **files, int num_files, flags flags) {
    if (flags.n) {
        if (num_files > 1) {
            if (flags.h) {
                printf("%d:%s\n", str_index, template[num]);
            } else {
                printf("%s:%d:%s\n", files[m], str_index, template[num]);
            }
        } else {
            printf("%d:%s\n", str_index, template[num]);
        }
    } else {
        if (num_files > 1) {
            if (flags.h) {
                printf("%s\n", template[num]);
            } else {
                printf("%s:%s\n", files[m], template[num]);
            }
        } else {
            printf("%s\n", template[num]);
        }
    }
}