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
