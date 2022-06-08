CC = gcc
СFLAGS := -Wall -Werror -Wextra -I. -g

SRC = s21_cat.c

.PHONY: all s21_cat test clean pyt

all: s21_cat

s21_cat:
	$(CC) $(CFLAGS) $(SRC) -o s21_cat

test: s21_cat
	bash t_cat.sh

clean:
	rm -rf s21_cat
	rm -rf log.txt

pyt:
	python3 ../../materials/linters/cpplint.py --extensions=c *.c *.h