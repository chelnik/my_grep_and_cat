CC = gcc -std=c11
СFLAGS = -Wall -Werror -Wextra 

SRC = s21_grep.c support_functions.c

.PHONY: all s21_grep test clean pyt leak go

all: s21_grep

s21_grep:
	$(CC) -D_GNU_SOURCE $(СFLAGS) $(SRC) -o s21_grep

test: all 
	s21_grep -f text.txt s21_grep.c
check:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
clean:
	rm -rf s21_grep
	rm -rf res1 res2
	rm log.txt
pyt:
	python3 ../../materials/linters/cpplint.py --extensions=c *.c *.h

leak:
	make
	leaks -atExit -- s21_grep

go:
	grep -e for s21_grep.c s21_grep.h Makefile text void world vova -v > res1
	s21_grep -e for s21_grep.c s21_grep.h Makefile text void world vova -v -s > res2
	diff res1 res2
