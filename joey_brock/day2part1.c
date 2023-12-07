#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int checkGame(char * inString) {
    return 0;
}

int main() {
    // Set up vars and file stuff
    int solution = 0;
    FILE *fileptr;
    fileptr = fopen("C:\\Users\\Joey\\Desktop\\advent_of_code_2023_files\\day2_input.txt", "r");
    int bufferSize = 200;
    char inLine[bufferSize];

    char * token;

    // Loop through the lines, adding up the solution numbers
    while (fgets(inLine, bufferSize, fileptr)) {
        token = strtok(inLine, " "); // Can ignore this one, just the word 'Game'
        token = strtok(NULL, ":"); // Should give game id
        long gameId = strtol(token, NULL, 10);
        
        token = strtok(NULL, ";");

        if 
    }

    printf("Solution is %d\n", solution);

    // Clean up
    fclose(fileptr);
    return 0;
}