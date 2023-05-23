#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.c"

static bool pt1(char** f);
static bool pt2(char** f);
static uint32_t get_prio(char item);
static bool string_contains_char(char* string, size_t len, char c);

bool day03(void) {
    char* file = read_file_to_string("./advent_of_code3.txt");

    char* file_pt1 = copy_str(file);
    char* file_pt1_orig = file_pt1;
    pt1(&file_pt1);
    free(file_pt1_orig);

    char* file_pt2 = copy_str(file);
    char* file_pt2_orig = file_pt2;
    pt2(&file_pt2);
    free(file_pt2_orig);

    free(file);

    printf("\n");
    return EXIT_SUCCESS;
}


static bool pt1(char** f) {
    char* line = strsep(f, "\n");


    uint32_t total = 0;

    while(line != NULL) {
        size_t line_len = strlen(line);
        size_t half_line_len = line_len / 2;

        char* first_half = calloc(half_line_len, sizeof(char));

        for(size_t i = 1; i <= line_len; i++) {
            if(i <= half_line_len) {
                first_half[i-1] = line[i-1];
            } else {
                if(string_contains_char(first_half, half_line_len, line[i-1])) {
                    total += get_prio(line[i-1]);

                    // GOTO BAD but ¯\_(ツ)_/¯
                    goto double_found;
                }
            }
        }

double_found:
        free(first_half);
        line = strsep(f, "\n");
    }

    printf("[*] (D03-1) Sum of priorities: %d\n", total);
}

static bool pt2(char** f) {
    char* line = strsep(f, "\n");

    uint32_t total = 0;

    while(line != NULL) {
        char* elve_group[3] = {0};

        elve_group[0] = line;
        elve_group[1] = strsep(f, "\n");
        elve_group[2] = strsep(f, "\n");

        size_t llen1 = strlen(elve_group[0]);
        size_t llen2 = strlen(elve_group[1]);
        size_t llen3 = strlen(elve_group[2]);

        // Iterate over every character in the first line
        for(size_t i = 0; i < llen1; i++) {
            char cur_char = elve_group[0][i];

            if(string_contains_char(elve_group[1], llen2, cur_char) && string_contains_char(elve_group[2], llen3, cur_char)) {
                total += get_prio(cur_char);
                goto next_group;
            }
        }

next_group:
        line = strsep(f, "\n");
    }

    printf("[*] (D03-2) Sum of priorities: %d\n", total);
}

static uint32_t get_prio(char item) {
    if(item >= 'a' && item <= 'z') {
        return item - ('a' - 1);
    } else if(item >= 'A' && item <= 'Z') {
        return item - ('A' - 27);
    } else {
        fprintf(stderr, "[!] Reached the unreachable, or something fucked up\n");
        exit(EXIT_FAILURE);
    }
}

static bool string_contains_char(char* string, size_t len, char c) {
    for(size_t i = 0; i < len; i++) {
        if(string[i] == c)
            return true;
    }

    return false;
}
