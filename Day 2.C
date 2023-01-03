#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#define BUFFER_SIZE 1024
#define WINDOW_WIDTH 80
#define WINDOW_HEIGHT 24

int main(int argc, char** argv) {
    // Initialize ncursed
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    // Get the screen dimensions
    int screen_width, screen_height;
    getmaxyx(stdscr, screen_height, screen_width);

    // Calculate the window position
    int window_x = (screen_width - WINDOW_WIDTH) / 2;
    int window_y = (screen_height - WINDOW_HEIGHT) / 2;

    // Create the window
    WINDOW* win = newwin(WINDOW_HEIGHT, WINDOW_WIDTH, window_y, window_x);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(win);

    // Set the window title
    char title[] = "editor";
    mvwaddstr(win, 0, (WINDOW_WIDTH - strlen(title)) / 2, title);
    wrefresh(win);

    // Initialize the buffer
    char buffer[BUFFER_SIZE];
    int buffer_pos = 0;

    // Main loop
    int ch;
    while ((ch = wgetch(win)) != 'q') {
        // Handle input
        switch(ch) {
            case KEY_F(1):
                // Open a file
                // TODO: implement file open dialog
                break;
            case KEY_F(2):
                // Save the file
                // TODO: implement file save dialog
                break;
            default:
                // Add the character to the buffer
                buffer[buffer_pos++] = ch;
                break;
        }

        // Clear the window
        werase(win);

        // Render the buffer
        mvwaddstr(win, 1, 1, buffer);

        // Refresh the window
        wrefresh(win);
    }

    // Clean up ncursed
    delwin(win);
    endwin();

    return 0;
}
