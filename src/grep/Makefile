FLAGS = -Wall -Wextra -Werror -std=c11 -pedantic

s21_grep: s21_grep.o
	gcc $(FLAGS) s21_grep.o -o s21_grep

s21_grep.o: s21_grep.c
	gcc $(FLAGS) -c s21_grep.c

test_grep:
	sh tests.sh

test_grep_multifile:
	sh tests_multifile.sh

clean:
	rm -rf *.out *.o s21_grep grep_result.txt program_result.txt