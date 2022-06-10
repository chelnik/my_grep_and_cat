#include "s21_grep.h"

int main(int argc, char const *argv[]) {
    if (argc == 1) {
        fprintf(stderr,
                "usage: grep [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B num] "
                "[-C[num]]\n"
                "        [-e pattern] [-f file] [--binary-files=value] "
                "[--color=when]\n"
                "        [--context[=num]] [--directories=action] [--label] "
                "[--line-buffered]\n"
                "        [--null] [pattern] [file ...]\n");
        return EXIT_FAILURE;
    } else if (argc <= 2) {
        return EXIT_FAILURE;
    }
    flags flags = {0};
    cheker_flags_ef(argc, argv, &flags);
    parser(argc, argv, flags);
    fclose(stdin);
    fclose(stdout);
    fclose(stderr);
    return 0;
}

void parser(int argc, char const *argv[], flags flags) {
    // для шаблона
    const char *template[100];
    int num_template = 0;
    // файлы с шаблонами
    const char *template_files[100];
    int num_template_files = 0;
    // массив файлов в которых читать
    const char *files[100];
    int num_files = 0;
    int errors = 0, flag_for_take_file = 0;
    memset(files, 0, sizeof(files));
    for (int i = 1; i < argc && !errors; i++) {
        int arg_length = strlen(argv[i]);
        if (argv[i][0] == '-') {
            for (int j = 1; j < arg_length && !errors; j++) {
                switch (argv[i][j]) {
                    case 'e':
                        flags.e = 1;
                        template[num_template++] = argv[++i];
                        if (argv[i + 1][0] != '-') {
                            files[num_files++] = argv[++i];
                        }
                        break;
                    case 'i':
                        flags.i = 1;
                        break;
                    case 'v':
                        flags.v = 1;
                        break;
                    case 'c':
                        flags.c = 1;
                        break;
                    case 'l':
                        flags.l = 1;
                        break;
                    case 'n':
                        flags.n = 1;
                        break;
                    case 'h':
                        flags.h = 1;
                        break;
                    case 's':
                        flags.s = 1;
                        break;
                    case 'f':
                        flags.f = 1;
                        template_files[num_template_files++] = argv[++i];
                        if (argv[i + 1][0] != '-') {
                            files[num_files++] = argv[++i];
                        }
                        break;
                    case 'o':
                        flags.o = 1;
                        break;
                    default:
                        fprintf(
                            stderr,
                            "grep: invalid option -- %s\n"
                            "usage: grep [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A "
                            "num] [-B num] [-C[num]]\n"
                            "        [-e pattern] [-f file] "
                            "[--binary-files=value] [--color=when]\n"
                            "        [--context[=num]] [--directories=action] "
                            "[--label] [--line-buffered]\n"
                            "        [--null] [pattern] [file ...]\n",
                            argv[i]);
                        fclose(stderr);
                        errors = 1;
                        break;
                }
            }
        } else {
            if (flags.there_are_ef_flags) {
                files[num_files++] = argv[i];
            } else {
                // конструкция что бы забирать файлы
                if (!flag_for_take_file) {
                    template[num_template++] = argv[i];
                    // что бы не брать флаги как файлы
                    if (argv[i + 1][0] != '-') {
                        files[num_files++] = argv[++i];
                        flag_for_take_file = 1;
                    }
                } else {
                    files[num_files++] = argv[i];
                }
            }
        }
    }
    // Указатель для массива
    char **str_array = NULL;
    if (flags.f) {
        // char str_array[100][256];
        str_array = (char **)malloc(100 * sizeof(char *));
        for (int i = 0; i < 100; i++) {
            str_array[i] = (char *)malloc(256 * sizeof(char));
        }
        template_files_opener(template_files, num_template_files, template,
                              &num_template, flags, str_array);
    }

    worker(files, num_files, template, num_template, flags);

    if (flags.f) {
        for (int i = 0; i < 100; i++) {
            free(str_array[i]);
        }
    }
    free(str_array);
}

// Перебирает файлы и шаблоны и выводит на экран  использует регулярные
// выражения
void worker(const char **files, int num_files, const char **template,
            int num_template, flags flags) {
    FILE *file = NULL;
    regex_t reegex;
    int value;

    for (int m = 0; m < num_files; m++) {
        if ((file = fopen(files[m], "r")) == NULL) {
            if (!flags.s) {
                fprintf(stderr, "grep: %s: No such file or directory\n",
                        files[m]);
                fclose(stderr);
            }
            continue;
        } else {
            int goodbye = 0;
            int enter_flag = 0;
            int number_of_matching_rows = 0, str_index = 0, case_flag = 0;
            case_flag = (flags.i) ? REG_ICASE : 0;
            char buf[500] = "";
            // переменные для флага l
            int index = 0;
            int index_ec = 0;
            // ------------------------------------------------- while file
            while (fgets(buf, 500, file) != NULL && goodbye == 0) {
                str_index++;
                for (int num = 0; num < num_template; num++) {
                    regcomp(&reegex, template[num], case_flag);
                    value = regexec(&reegex, buf, 0, NULL, 0);
                    index++;
                    index_ec += value;
                    regfree(&reegex);
                    // regfree должен пройти по всему файлу и если во всем файле
                    // не value отдаст regnomatch

                    if (flags.l) {
                        if (value == 0 || (value == REG_NOMATCH && flags.v)) {
                            function_for_flag_l(m, files, num_files, flags);
                            // выходит из цикла while
                            goodbye = 1;
                            // break;
                        }
                    } else if (flags.c) {
                        if (value == 0 && !flags.v) {
                            number_of_matching_rows++;
                            break;
                            // Инвертирует смысл поиска соответствий.
                        } else if (value == REG_NOMATCH && flags.v) {
                            number_of_matching_rows++;
                            break;
                        }
                    } else if (flags.o && !flags.v && !flags.l && !flags.c &&
                               value == 0) {
                        // Для флага о
                        function_for_flag_o(num, template, str_index, m, files,
                                            num_files, flags);

                        // ---
                    } else {
                        // базовый случай вывода
                        // ==============================================
                        if ((flags.v && value == REG_NOMATCH) ||
                            (!flags.v && value == 0)) {
                            // номер строки
                            if (flags.n) {
                                // для нескольких файлов
                                if (num_files > 1) {
                                    if (flags.h) {
                                        printf("%d:%s", str_index, buf);
                                        enter_flager(&enter_flag, buf, flags);
                                        break;
                                    } else {
                                        printf("%s:%d:%s", files[m], str_index,
                                               buf);
                                        enter_flager(&enter_flag, buf, flags);
                                        break;
                                    }

                                } else {
                                    // базовый случай вывода
                                    printf("%d:%s", str_index, buf);
                                    enter_flager(&enter_flag, buf, flags);
                                    break;
                                }
                            } else {
                                if (num_files > 1) {
                                    if (flags.h) {
                                        printf("%s", buf);
                                        enter_flager(&enter_flag, buf, flags);
                                        break;
                                    } else {
                                        printf("%s:%s", files[m], buf);
                                        enter_flager(&enter_flag, buf, flags);
                                        break;
                                    }
                                } else {
                                    // базовый случай вывода
                                    printf("%s", buf);
                                    enter_flager(&enter_flag, buf, flags);
                                    break;
                                }
                            }

                        } else if (flags.v) {
                            // для случая v flag когда перебирается много
                            // шаблонов
                            // вместо else сделал if (flags.v)
                            break;
                        }
                    }
                }
            }
            // -------------------------------------------- while file

            if ((flags.l && flags.c && !flags.v && (index == index_ec))) {
                if (num_files > 1 && !flags.h) {
                    printf("%s:0\n", files[m]);
                } else {
                    printf("0\n");
                }
            }

            if (flags.c && !flags.l) {
                if (num_files > 1) {
                    if (flags.h) {
                        printf("%d\n", number_of_matching_rows);
                    } else {
                        printf("%s:%d\n", files[m], number_of_matching_rows);
                    }

                } else {
                    printf("%d\n", number_of_matching_rows);
                }
            }
            fclose(file);
            if (enter_flag == 1) {
                printf("\n");
            }
        }
    }
}

void parser(int argc, char const *argv[], flags flags);
void worker(const char **files, int num_files, const char **template,
            int num_template, flags flags);
void template_files_opener(const char **template_files, int num_template_files,
                           const char **template, int *num_template,
                           flags flags, char **str_array);
void cheker_flags_ef(int argc, char const *argv[], flags *flags);
void enter_flager(int *enter_flag, char *buf, flags flags);