#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int getPower(char * inString) {
    // Returns 1 if game is invalid, 0 if game is valid
    int num = 0;
    int redMax = 0;
    int greenMax = 0;
    int blueMax = 0;
    char color;

    char * token = strtok(inString, ";");
    while (token != NULL) {
        for (int k = 0; k < strlen(token); k++) {
            if (isdigit(token[k])) {
                if (isdigit(token[k + 1])) {
                    num = 10 * (token[k] - '0') + (token[k + 1] - '0');
                    color = token[k + 3];
                    k = k + 6;
                } else { 
                    num = token[k] - '0';
                    color = token[k + 2];
                    k = k + 5;
                }
                switch (color) {
                    case 'r':
                        if (num > redMax) {
                            redMax = num;
                        }
                        break;
                    case 'b':
                        if (num > blueMax) {
                            blueMax = num;
                        }
                        break;
                    case 'g':
                        if (num > greenMax) {
                            greenMax = num;
                        }
                        break;
                    default:
                        break;
                }
            } else {
                // Do nothing here
            }
        }
        token = strtok(NULL, ";");
    }


    
    return redMax * greenMax * blueMax;
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

        token = strtok(NULL, "\n");
        solution += getPower(token);
        
    }

    printf("Solution is %d\n", solution);

    // Clean up
    fclose(fileptr);
    return 0;
}