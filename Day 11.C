#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

#define N 8  // Number of cities

int dist[N][N];  // Distance between each pair of cities
int tour[N];  // Current tour
bool used[N];  // Keep track of which cities have been visited
int min_tour_length = INT_MAX;  // Keep track of the length of the shortest tour found so far

// Function to calculate the distance between two cities
int get_distance(int x1, int y1, int x2, int y2) {
    return (int) round(sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

// Function to find the tour length
int get_tour_length(int tour[N]) {
    int length = 0;
    for (int i = 0; i < N - 1; i++) {
        length += dist[tour[i]][tour[i + 1]];
    }
    length += dist[tour[N - 1]][tour[0]];
    return length;
}

// Recursive function to generate all possible tours
void generate_tours(int step) {
    if (step == N) {
        int tour_length = get_tour_length(tour);
        if (tour_length < min_tour_length) {
            min_tour_length = tour_length;
        }
    } else {
        for (int i = 0; i < N; i++) {
            if (!used[i]) {
                tour[step] = i;
                used[i] = true;
                generate_tours(step + 1);
                used[i] = false;
            }
        }
    }
}

int main() {
    // Example coordinates for N = 8 cities
    int x[N] = {1, 2, 3, 4, 5, 6, 7, 8};
    int y[N] = {1, 2, 3, 4, 5, 6, 7, 8};

    // Calculate the distances between each pair of cities
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            dist[i][j] = get_distance(x[i], y[i], x[j], y[j]);
            dist[j][i] = dist[i][j];
        }
    }

    generate_tours(0);

    printf("Shortest tour length: %d\n", min_tour_length);

    return 0;
}
