#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int checkGame(char * inString) {
    // Returns 1 if game is invalid, 0 if game is valid
    int num = 0;
    int red = 12;
    int green = 13;
    int blue = 14;
    char color;

    for (int k = 0; k < strlen(inString); k++) {
        if (isdigit(inString[k])) {
            if (isdigit(inString[k + 1])) {
                num = 10 * (inString[k] - '0') + (inString[k + 1] - '0');
                color = inString[k + 3];
                k = k + 6;
            } else { 
                num = inString[k] - '0';
                color = inString[k + 2];
                k = k + 5;
            }
            switch (color) {
                case 'r':
                    if (num > red) {
                        return 1;
                    }
                    break;
                case 'b':
                    if (num > blue) {
                        return 1;
                    }
                    break;
                case 'g':
                    if (num > green) {
                        return 1;
                    }
                    break;
                default:
                    break;
            }
        } else {
            // Do nothing here
        }

    }
    return 0;
}

int main() {
    // Set up vars and file stuff
    long solution = 0;
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
        
        printf("Checking game %d...\n", gameId);
        token = strtok(NULL, ";");
        while (token != NULL) {
            if (checkGame(token) == 1) {
                solution += gameId;
                break;
            }


            token = strtok(NULL, ";");
        }
    }

    //Coded this to add up the invalid games instead of the valid games. So subtract it..
    long total = 100*101/2;
    solution = total - solution;

    printf("Solution is %d\n", solution);

    // Clean up
    fclose(fileptr);
    return 0;
}