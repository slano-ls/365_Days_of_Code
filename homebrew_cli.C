
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PACKAGE_NAME_LENGTH 50

void display_packages(WINDOW *win, char **packages, int num_packages) {
    int i;
    wprintw(win, "Installed Homebrew Packages:\n");
    wprintw(win, "---------------------------\n");
    for (i = 0; i < num_packages; i++) {
        wprintw(win, "%s\n", packages[i]);
    }
    wrefresh(win); // Refresh the window after printing the contents
}

int main() {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char **packages = NULL;
    int num_packages = 0;
    int max_packages = 0;

    // Open a pipe to execute 'brew list' command and read the output
    fp = popen("brew list", "r");
    if (fp == NULL) {
        printf("Error executing Homebrew command!\n");
        return 1;
    }

    // Read the output line by line and store the package names
    while ((read = getline(&line, &len, fp)) != -1) {
        line[strcspn(line, "\n")] = '\0'; // Remove the newline character

        // Dynamically allocate memory for each package
        char *package = (char*) malloc((strlen(line) + 1) * sizeof(char));
        strcpy(package, line);

        // Expand the packages array if necessary
        if (num_packages >= max_packages) {
            max_packages += 10;
            packages = (char**) realloc(packages, max_packages * sizeof(char *));
        }

        // Add the package to the array
        packages[num_packages] = package;
        num_packages++;
    }

    // Close the pipe and free the allocated resources
    pclose(fp);
    if (line)
        free(line);

    // Initialize ncurses
    initscr();
    cbreak();
    noecho();

    // Create a new window
    WINDOW *win = newwin(20, 40, 0, 0);

    // Display the packages in the window
    display_packages(win, packages, num_packages);

    // Wait for a key press before exiting
    getch();

    // Clean up ncurses
    delwin(win);
    endwin();

    // Free the allocated package names
    for (int i = 0; i < num_packages; i++) {
        free(packages[i]);
    }
    free(packages);

    return 0;
}
