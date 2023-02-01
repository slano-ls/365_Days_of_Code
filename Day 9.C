#include "Day 9.h"

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    initscr();
    cbreak();
    noecho();

    int choice;

    while (1) {
        clear();
        mvprintw(0, 0, "Select an option:\n");
        mvprintw(1, 0, "1. Open Terminal\n");
        mvprintw(2, 0, "2. Close Terminal\n");
        mvprintw(3, 0, "3. Quit\n");
        refresh();

        choice = getch();
        switch (choice) {
            case '1':
                system("open -a Terminal");
                break;
            case '2':
                system("kill $(ps -ef | grep Terminal | grep -v grep | awk '{print $2}')");
                break;
            case '3':
                endwin();
                exit(0);
                break;
            default:
                break;
        }
    }

    endwin();
    return 0;
}
