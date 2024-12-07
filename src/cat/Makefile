FLAGS = -Wall -Wextra -Werror -std=c11 -pedantic

s21_cat: s21_cat.o
	gcc $(FLAGS) s21_cat.o -o s21_cat

s21_cat.o: s21_cat.c
	gcc $(FLAGS) -c s21_cat.c

test_cat:
	sh tests.sh

test_cat_multifile:
	sh tests_multifile.sh

clean:
	rm -rf *.out *.o s21_cat cat_result.txt program_result.txt