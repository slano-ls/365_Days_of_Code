//      $$$$$$\   $$$$$$\  $$$$$$$\      $$$$$$$\                                               $$$$$$\       $$$$$$\                  $$\
//     $$ ___$$\ $$  __$$\ $$  ____|     $$  __$$\                                             $$  __$$\     $$  __$$\                 $$ |
//     \_/   $$ |$$ /  \__|$$ |          $$ |  $$ | $$$$$$\  $$\   $$\  $$$$$$$\      $$$$$$\  $$ /  \__|    $$ /  \__| $$$$$$\   $$$$$$$ | $$$$$$\
//        $$$$$ / $$$$$$$\  $$$$$$$\     $$ |  $$ | \____$$\ $$ |  $$ |$$  _____|    $$  __$$\ $$$$\         $$ |      $$  __$$\ $$  __$$ |$$  __$$\
//       \___$$\ $$  __$$\ \_____$$\     $$ |  $$ | $$$$$$$ |$$ |  $$ |\$$$$$$\      $$ /  $$ |$$  _|        $$ |      $$ /  $$ |$$ /  $$ |$$$$$$$$ |
//     $$\   $$ |$$ /  $$ |$$\   $$      $$ |  $$ |$$  __$$ |$$ |  $$ | \____$$\     $$ |  $$ |$$ |          $$ |  $$\ $$ |  $$ |$$ |  $$ |$$   ____|
//     \$$$$$$  | $$$$$$  |\$$$$$$  |    $$$$$$$  |\$$$$$$$ |\$$$$$$$ |$$$$$$$  |    \$$$$$$  |$$ |          \$$$$$$  |\$$$$$$  |\$$$$$$$ |\$$$$$$$\
//      \______/  \______/  \______/     \_______/  \_______| \____$$ |\_______/      \______/ \__|           \______/  \______/  \_______| \_______|
//                                                             $$\   $$ |
//                                                             \$$$$$$  |
//                                                              \______/
// Author : Saihaj Law
// Date : January 6th
// Project : Unix HEAD/TAIL simplified version
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE_BUFFER_SIZE 4096

int main(int argc, char **argv) {
  // Parse the command line arguments
  if (argc < 2) {
    fprintf(stderr, "Usage: %s [head|tail] [-n NUM] [FILE]\n", argv[0]);
    return 1;
  }
  int num_lines = 10;
  char *utility = argv[1];
  if (strcmp(utility, "head") != 0 && strcmp(utility, "tail") != 0) {
    fprintf(stderr, "Error: First argument must be either 'head' or 'tail'\n");
    return 1;
  }
  if (argc >= 4 && strcmp(argv[2], "-n") == 0) {
    num_lines = atoi(argv[3]);
  }
  char *filename = (argc >= 5) ? argv[4] : NULL;

  // Open the input file (or use stdin if no file was specified)
  FILE *fp;
  if (filename != NULL) {
    fp = fopen(filename, "r");
    if (fp == NULL) {
      perror("Error opening file");
      return 1;
    }
  } else {
    fp = stdin;
  }

  // Read the file line by line
  char line[LINE_BUFFER_SIZE];
  int line_number = 0;
  char **lines = NULL;
  int num_lines_allocated = 0;
  while (fgets(line, LINE_BUFFER_SIZE, fp) != NULL) {
    // Store the line in a buffer if we are using the "tail" utility
    if (strcmp(utility, "tail") == 0) {
      if (line_number == num_lines_allocated) {
        num_lines_allocated *= 2;
        lines = (char**)realloc(lines, num_lines_allocated * sizeof(char*));
      }
      lines[line_number] = strdup(line);
    }
    // Print the line if we are using the "head" utility
    if (strcmp(utility, "head") == 0 && line_number < num_lines) {
      printf("%s", line);
    }
    line_number++;
  }

  // Print the last N lines if we are using the "tail" utility
  if (strcmp(utility, "tail") == 0) {
    for (int i = line_number - num_lines; i < line_number; i++) {
      printf("%s", lines[i]);
    }
  }

  // Clean up
  if (strcmp(utility, "tail") == 0) {
    for (int i = 0; i < line_number; i++) {
      free(lines[i]);
    }
    free(lines);
  }
  if (filename != NULL){
      fclose(fp);
  }
  return 0;
}
