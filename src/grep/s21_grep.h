#ifndef S_21_GREP_H
#define S_21_GREP_H
#define MAX_STRING_LENGTH 20
#define _GNU_SOURCE
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void process_programm();
FILE *open_file(char *filename, char *mode);
void flag_e(regex_t rg, char *line, char *pattern, char *filename, int size);
void flag_i(regex_t rg, char *line, char *pattern, char *filename, int size);
void flag_v(regex_t rg, char *line, char *pattern, char *filename, int size);
void flag_c(regex_t rg, char *line, char *pattern, int *match_lines);
void flag_l(regex_t rg, char *line, char *pattern, char *filename,
            char **printed_filename);
void flag_n(regex_t rg, char *line, char *pattern, int line_number,
            char *filename, int size);
void free_from_files(char **files, int size);
char **allocate_for_files(char **files, int size);
char **read_files(int argc, char *argv[], char *pattern, char *flag, int *size);

#endif