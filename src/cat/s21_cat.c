#include "s21_cat.h"

int main(int argc, char const *argv[]) {
    flags_all_typedef flags;
    memset(&flags, 0, sizeof(struct flag_all));
    int errors = 0;
    for (int i = 1; i < argc && errors == 0; i++) {
        if (argv[i][0] == '-') {
            for (size_t j = 1; j < strlen(argv[i]); j++) {
                switch (argv[i][j]) {
                    case 'b':
                        flags.FLAG_B = flags.FLAG_N = 1;
                        break;
                    case 'e':
                        flags.FLAG_E = flags.FLAG_V = 1;
                        break;
                    case 'E':
                        flags.FLAG_E = 1;
                        break;
                    case 'n':
                        flags.FLAG_N = 1;
                        break;
                    case 's':
                        flags.FLAG_S = 1;
                        break;
                    case 't':
                        flags.FLAG_T = flags.FLAG_V = 1;
                        break;
                    case 'T':
                        flags.FLAG_T = flags.FLAG_V = 1;
                        break;
                    case 'v':
                        flags.FLAG_V = 1;
                        break;
                    case '-': {
                        if (strcmp((argv[i]), "--number-nonblank") == 0) {
                            flags.FLAG_B = 1;
                            j += 17;
                        } else if (strcmp((argv[i]), "--number") == 0) {
                            flags.FLAG_N = 1;
                            j += 8;
                        } else if (strcmp((argv[i]), "--squeeze-blank") == 0) {
                            flags.FLAG_S = 1;
                            j += 15;
                        }

                        break;
                    }
                    default:
                        printf("cat: illegal option -- %c\n", argv[i][j]);
                        printf("usage: cat [-benstuv] [file ...]\n");
                        errors++;
                        break;
                }
            }
        }
    }
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            new_opener(argv[i], flags);
        }
    }

    return 0;
}

int new_opener(const char *filename, flags_all_typedef flags) {
    int ch, prev;
    FILE *fp;
    if ((fp = fopen(filename, "r")) == NULL) {
        printf("cat: %s: No such file or directory\n", filename);
        return 1;
    }
    size_t void_string_flag = 0, i = 0;
    for (prev = '\n'; (ch = getc(fp)) != EOF; prev = ch) {
        if (prev == '\n') {
            if (flags.FLAG_S) {
                if (ch == '\n') {
                    if (void_string_flag) continue;
                    void_string_flag = 1;
                } else {
                    void_string_flag = 0;
                }
            }
            if (flags.FLAG_N) {
                if (!flags.FLAG_B || ch != '\n') {
                    printf("%6lu\t", ++i);
                }
            }
        }
        if (ch == '\n') {
            if (flags.FLAG_E) printf("%c", '$');
        } else if (ch == '\t') {
            if (flags.FLAG_T) {
                printf("^I");
                continue;
            }
        } else if (flags.FLAG_V) {
            if ((int)ch >= 0 && (int)ch <= 31) {
                printf("^%c", ch + '@');
            } else if ((int)ch >= 128 && (int)ch <= 159) {
                printf("M-^%c", ch + '@' - 128);
            } else if (ch == 127) {
                printf("^?");
            }
        }
        printf("%c", ch);
    }
    fclose(fp);
    return 0;
}
