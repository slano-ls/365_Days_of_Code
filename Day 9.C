#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: manager [open|close] [app name]\n");
        return 1;
    }

    char *command;
    if (strcmp(argv[1], "open") == 0) {
        command = malloc(strlen("open -a ") + strlen(argv[2]) + 1);
        strcpy(command, "open -a ");
        strcat(command, argv[2]);
    } else if (strcmp(argv[1], "close") == 0) {
        command = malloc(strlen("kill $(ps -ef | grep ") + strlen(argv[2]) + strlen(" | grep -v grep | awk '{print $2}')") + 1);
        strcpy(command, "kill $(ps -ef | grep ");
        strcat(command, argv[2]);
        strcat(command, " | grep -v grep | awk '{print $2}')");
    } else {
        printf("Usage: manager [open|close] [app name]\n");
        return 1;
    }

    system(command);
    free(command);

    return 0;
}
