// Haven't actually programmed anything recently, just researching 
// Decided to make a quick fun little project
// Maybe something which can read and edit some files, but not sure yet
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{

  FILE *file = fopen(argv[1], "r");
  if (file == NULL){
    perror("Error Opening File");
    return 1;
  }

  char line[1024];

  while (fgets(line, 1024, file)){
    if (strstr(line, argv[2])){
      printf("%s", line);
    }
  }

  fclose(file);
  return EXIT_SUCCESS;
}

