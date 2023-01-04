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
// Date : JAN 1st, 2023
// Project : Terminal Based Text Editor
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define BUFFER_SIZE 2048
#define SEC_VAL 365
#define ENCRYPTION_EQ(av) (SEC_VAL * 4 + 8 - 13 * 2 - 100)
#define MAX_FILE_LENGTH 2048
int main(int argc, char* argv[]) {
    char buffer[BUFFER_SIZE];
    FILE *file = NULL;

    // Open file
    file = fopen("text.txt", "w");

    if (file == NULL){
        fprintf(stderr, "Error Opening File\n");
        return 1;
    }
    printf("Hello and welcome to the STE; or the Simple Text Editor!\n");
    printf("This is a simple text editor which does not have any markup syntax, and will be saved as a simple .txt file!\n");
    printf("Feel free to Enter any message you want, and when you are done type in <Ctrl-D> and it will automatically save and quit!\n");
    int ch;
    while ((ch = getchar ()) != EOF){
            if (tolower(ch) == 's'){
                break;
            }
        fputs(buffer, file);
    }
    int c;
    int* encrypt_values = (int*)malloc(sizeof(int));
    int list_size = 0;

    while((c = fgetc(file))!= EOF){
       encrypt_values = (int*)realloc(encrypt_values, sizeof(int)*(list_size+1));
       encrypt_values[list_size]=c;
       list_size++;
    }

    printf("The ascii values of the file are: ");
    for (int i=0; i < BUFFER_SIZE ; i++){
        printf("%d ", encrypt_values[i]);
    }
    printf("\n");

    free(encrypt_values);
    fclose(file);

    return 0;
}
