#include "s21_cat.h"

int main(int argc, char *argv[]) {
  char *flag = "";
  char *flags[10] = {"-b", "--number_nonblank", "-e", "-E", "-n", "--number",
                     "-s", "--squeeze-blank",   "-t", "-T"};
  int size = 0;

  for (int i = 1; i < argc; i++) {
    char *current_argument = argv[i];
    int check = 0;
    if (!check) {
      for (int j = 0; j < 10; j++) {
        if (strcmp(flags[j], current_argument) == 0) {
          flag = current_argument;
          check = 1;
        }
      }
    }
  }

  char **files = read_files(argc, argv, flag, &size);

  for (int i = 0; i < size; i++) {
    process_programm(files[i], flag);
  }
  free_from_files(files, size);
}

void process_programm(char *filename, char *mode) {
  int line_number = 1;
  int chars[] = {'\n', '\n'};
  FILE *fptr = read_file(filename, "r");

  if (fptr != NULL) {
    chars[1] = fgetc(fptr);
    int flag = 1;
    while (chars[1] != EOF) {
      if (strcmp(mode, "-b") == 0 || strcmp(mode, "--number-nonblank") == 0) {
        flag_b(chars, &line_number);
      } else if (strcmp(mode, "-e") == 0) {
        flag_e(chars);
        flag_v(chars);
      } else if (strcmp(mode, "-E") == 0) {
        flag_e(chars);
      } else if (strcmp(mode, "-n") == 0 || strcmp(mode, "--number") == 0) {
        flag_n(chars, &line_number);
      } else if (strcmp(mode, "-s") == 0 ||
                 strcmp(mode, "--squeeze-blank") == 0) {
        flag_s(chars, fptr, &flag);
      } else if (strcmp(mode, "-t") == 0) {
        if (flag_t(chars) == 0) {
          flag_v(chars);
        }
      } else if (strcmp(mode, "-T") == 0) {
        if (flag_t(chars) == 0) {
          printf("%c", chars[1]);
        }
      } else {
        printf("%c", chars[1]);
      }
      chars[0] = chars[1];
      chars[1] = fgetc(fptr);
    }
  }
  fclose(fptr);
}

FILE *read_file(char *filename, char *mode) {
  FILE *fptr = NULL;

  if (fopen(filename, mode) != NULL) {
    fptr = fopen(filename, mode);
  } else {
    printf("%s: Not such file\n", filename);
  }

  return fptr;
}

void flag_b(int chars[], int *line_number) {
  if (chars[1] != '\n' && chars[0] == '\n') {
    printf("%6d\t", *line_number);
    *line_number = *line_number + 1;
  }
  printf("%c", chars[1]);
}

void flag_n(int chars[], int *line_number) {
  if (chars[0] == '\n') {
    printf("%6d\t", *line_number);
    *line_number = *line_number + 1;
  }
  printf("%c", chars[1]);
}

void flag_s(int chars[], FILE *file, int *flag) {
  if (ftell(file) == 1 && chars[1] == '\n' && *flag == 1) {
    printf("\n");
    *flag = 0;
  } else if (ftell(file) != 1 && chars[1] != '\n' && chars[0] == '\n' &&
             *flag == 1) {
    printf("\n");
    *flag = 0;
  } else if (ftell(file) != 1 && chars[1] == '\n' && chars[0] == '\n' &&
             *flag == 1) {
    printf("\n\n");
    *flag = 0;
  }

  if (chars[1] != '\n') {
    printf("%c", chars[1]);
    *flag = 1;
  }
}

void flag_e(int chars[]) {
  if (chars[1] == '\n') {
    printf("$");
  }
}

void flag_v(int chars[]) {
  if ((chars[1] >= 0 && chars[1] <= 8) || (chars[1] >= 11 && chars[1] <= 31)) {
    printf("^%c", chars[1] + 64);
  } else if (chars[1] == 127) {
    printf("^?");
  } else {
    printf("%c", chars[1]);
  }
}

int flag_t(int chars[]) {
  int result = 0;
  if (chars[1] == '\t') {
    printf("^I");
    result = 1;
  }
  return result;
}

// Free memory the array of files
void free_from_files(char **files, int size) {
  for (int i = 0; i < size; i++) {
    free(files[i]);
  }
  free(files);
}

// Allocating memory to array for files and reading files into it
char **read_files(int argc, char *argv[], char *flag, int *size) {
  for (int i = 1; i < argc; i++) {
    if (strcmp(flag, argv[i]) != 0) {
      *size = *size + 1;
    }
  }

  char **files = (char **)malloc(*size * sizeof(char *));

  for (int i = 0; i < *size; i++) {
    files[i] = (char *)malloc(MAX_STRING_LENGTH * sizeof(char));
  }

  int j = 0;
  for (int i = 1; i < argc; i++) {
    if (strcmp(flag, argv[i]) != 0) {
      strcpy(files[j], argv[i]);
      j += 1;
    }
  }

  return files;
}
