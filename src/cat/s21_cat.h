#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct flag_all {
    // нумерует только непустые строки
    int FLAG_B;
    // конец строки доллар $
    int FLAG_E;
    // нумерует все выходные строки
    int FLAG_N;
    // сжимает строки
    int FLAG_S;
    // отображает табы как ^I
    int FLAG_T;
    // выводит скрытые символы
    int FLAG_V;
} flags_all_typedef;

int new_opener(const char *filename, flags_all_typedef flags);

#endif  // SRC_CAT_S21_CAT_H_
