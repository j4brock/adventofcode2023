#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main() {
    // Set up vars and file stuff
    int solution = 1;
    FILE *fileptr;
    fileptr = fopen("C:\\Users\\Joey\\Desktop\\advent_of_code_2023_files\\day6_input.txt", "r");
    int numChars = 40;
    char inLine[numChars + 2];
    int numRaces = 4;
    int times[numRaces];
    int distances[numRaces];

    fgets(inLine, numChars, fileptr);
    strtok(inLine, " ");

    for (int i = 0; i < numRaces; i++) {
        times[i] = strtol(strtok(NULL, " "), NULL, 10);
    }
    

    fgets(inLine, numChars, fileptr);
    strtok(inLine, " ");

    for (int i = 0; i < numRaces; i++) {
        distances[i] = strtol(strtok(NULL, " "), NULL, 10);
    }

    int timeToRun;
    int distanceRan;
    int numWaysToWin;
    for (int i = 0; i < numRaces; i++) { // Loop through each race
        numWaysToWin = 0;
        for (int j = 1; j < times[i] - 1; j++) { // Loop through each (useful) button down time
            // j is speed
            timeToRun = times[i] - j;
            distanceRan = timeToRun * j;
            if (distanceRan > distances[i]) {
                numWaysToWin++;
            }
        }
        solution *= numWaysToWin;
    }
    

    printf("Solution is %d\n", solution);

    // Clean up
    fclose(fileptr);
    return 0;
}