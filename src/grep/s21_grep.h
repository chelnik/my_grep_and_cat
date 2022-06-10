#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct flag_s {
    int e;
    int i;
    int v;
    int c;
    int l;
    int n;
    int h;
    int s;
    int f;
    int o;
    int there_are_ef_flags;
} flags;

void parser(int argc, char const *argv[], flags flags);
void worker(const char **files, int num_files, const char **template,
            int num_template, flags flags);
void template_files_opener(const char **template_files, int num_template_files,
                           const char **template, int *num_template,
                           flags flags, char **str_array);
void cheker_flags_ef(int argc, char const *argv[], flags *flags);
void enter_flager(int *enter_flag, char *buf, flags flags);

void function_for_flag_l(int m, const char **files, int num_files, flags flags);
void function_for_flag_o(int num, const char **template, int str_index, int m,
                         const char **files, int num_files, flags flags);
#endif  // SRC_GREP_S21_GREP_H_
