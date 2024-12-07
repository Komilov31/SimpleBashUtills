#include "s21_grep.h"

int main(int argc, char *argv[]) {
  char *flag = "";
  char *pattern = "";
  char *flags[6] = {"-e", "-i", "-v", "-c", "-l", "-n"};
  int flag_position = 0;
  int size = 0;

  for (int i = 1; i < argc; i++) {
    char *current_argument = argv[i];
    int check = 0;
    if (!check) {
      for (int j = 0; j < 6; j++) {
        if (strcmp(flags[j], current_argument) == 0) {
          flag = current_argument;
          flag_position = i;
          check = 1;
        }
      }
    }
  }

  if (flag_position != 0) {
    pattern = argv[flag_position + 1];
  } else {
    pattern = argv[1];
  }

  char **files = read_files(argc, argv, pattern, flag, &size);

  for (int i = 0; i < size; i++) {
    process_programm(files[i], flag, pattern, size);
  }
  free_from_files(files, size);
}

FILE *open_file(char *filename, char *mode) {
  FILE *fptr = fopen(filename, mode);

  if (fptr == NULL) {
    printf("%s: Not such file\n", filename);
  }

  return fptr;
}

void process_programm(char *filename, char *flag, char *pattern, int size) {
  FILE *fptr = open_file(filename, "r");
  int match_lines = 0;
  int line_number = 1;
  char *printed_filename = "";
  char *line = NULL;
  size_t len = 0;
  regex_t rg;

  if (fptr != NULL) {
    int read = getline(&line, &len, fptr);
    while (read != EOF) {
      if (strcmp(pattern, "") != 0) {
        if (strcmp(flag, "-e") == 0) {
          flag_e(rg, line, pattern, filename, size);
        } else if (strcmp(flag, "-i") == 0) {
          flag_i(rg, line, pattern, filename, size);
        } else if (strcmp(flag, "-v") == 0) {
          flag_v(rg, line, pattern, filename, size);
        } else if (strcmp(flag, "-c") == 0) {
          flag_c(rg, line, pattern, &match_lines);
        } else if (strcmp(flag, "-l") == 0) {
          if (strcmp(filename, printed_filename) != 0) {
            flag_l(rg, line, pattern, filename, &printed_filename);
          }
        } else if (strcmp(flag, "-n") == 0) {
          flag_n(rg, line, pattern, line_number, filename, size);
        }
      } else {
        flag_e(rg, line, pattern, filename, size);
      }
      read = getline(&line, &len, fptr);
      line_number++;
    }
    if (strcmp(flag, "-c") == 0 && size < 2) {
      printf("%d\n", match_lines);
    } else if (strcmp(flag, "-c") == 0 && size >= 2) {
      printf("%s:%d\n", filename, match_lines);
    }
  }

  free(line);
  fclose(fptr);
}

void flag_e(regex_t rg, char *line, char *pattern, char *filename, int size) {
  if (regcomp(&rg, pattern, 0) == 0) {
    if (regexec(&rg, line, 0, NULL, 0) == 0) {
      if (size == 1) {
        printf("%s", line);
      } else {
        printf("%s:%s", filename, line);
      }
    }
    regfree(&rg);
  }
}

void flag_i(regex_t rg, char *line, char *pattern, char *filename, int size) {
  if (regcomp(&rg, pattern, REG_ICASE) == 0) {
    if (regexec(&rg, line, 0, NULL, 0) == 0) {
      if (size == 1) {
        printf("%s", line);
      } else {
        printf("%s:%s", filename, line);
      }
    }
    regfree(&rg);
  }
}

void flag_v(regex_t rg, char *line, char *pattern, char *filename, int size) {
  if (regcomp(&rg, pattern, 0) == 0) {
    if (regexec(&rg, line, 0, NULL, 0) != 0) {
      if (size == 1) {
        printf("%s", line);
      } else {
        printf("%s:%s", filename, line);
      }
    }
    regfree(&rg);
  }
}

void flag_c(regex_t rg, char *line, char *pattern, int *match_lines) {
  if (regcomp(&rg, pattern, 0) == 0) {
    if (regexec(&rg, line, 0, NULL, 0) == 0) {
      *match_lines = *match_lines + 1;
    }
    regfree(&rg);
  }
}

void flag_l(regex_t rg, char *line, char *pattern, char *filename,
            char **printed_filename) {
  if (regcomp(&rg, pattern, 0) == 0) {
    if (regexec(&rg, line, 0, NULL, 0) == 0) {
      printf("%s\n", filename);
      *printed_filename = filename;
    }
    regfree(&rg);
  }
}

void flag_n(regex_t rg, char *line, char *pattern, int line_number,
            char *filename, int size) {
  if (regcomp(&rg, pattern, 0) == 0) {
    if (regexec(&rg, line, 0, NULL, 0) == 0) {
      if (size != 1) {
        printf("%s:%d:%s", filename, line_number, line);
      } else {
        printf("%d:%s", line_number, line);
      }
    }
    regfree(&rg);
  }
}

// Free memory the array of files
void free_from_files(char **files, int size) {
  for (int i = 0; i < size; i++) {
    free(files[i]);
  }
  free(files);
}

// Allocating memory to array for files and reading files into ita
char **read_files(int argc, char *argv[], char *pattern, char *flag,
                  int *size) {
  for (int i = 1; i < argc; i++) {
    if (strcmp(pattern, argv[i]) != 0 && strcmp(flag, argv[i]) != 0) {
      *size = *size + 1;
    }
  }

  char **files = (char **)malloc(*size * sizeof(char *));

  for (int i = 0; i < *size; i++) {
    files[i] = (char *)malloc(MAX_STRING_LENGTH * sizeof(char));
  }

  int j = 0;
  for (int i = 1; i < argc; i++) {
    if (strcmp(pattern, argv[i]) != 0 && strcmp(flag, argv[i]) != 0) {
      strcpy(files[j], argv[i]);
      j += 1;
    }
  }

  return files;
}