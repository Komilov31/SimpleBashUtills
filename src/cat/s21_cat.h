#ifndef S_21_CAT_H
#define S_21_CAT_H
#define MAX_STRING_LENGTH 20
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void process_programm(char *filename, char *mode);
void flag_b(int chars[], int *line_number);
void flag_n(int chars[], int *line_number);
void flag_s(int chars[], FILE *file, int *flag);
void flag_e(int chars[]);
int flag_t(int chars[]);
void flag_v(int chars[]);
FILE *read_file(char *filename, char *mode);
char **read_files(int argc, char *argv[], char *flag, int *size);
void free_from_files(char **files, int size);

#endif