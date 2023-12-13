#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void getDiff(long long * inVec, long long numEntries, long long * outVec) {
    for (int i = 0; i < numEntries - 1; i++) {
        *(outVec + i) = *(inVec + i + 1) - *(inVec + i);
    }
}

int checkDiff(long long * inVec, long long numEntries) {
    int result = 1;
    for (int i = 0; i < numEntries; i++) {
        result = result && *(inVec + i) == 0;
        if (result == 0) {
            return result;
        }
    }
    return result;
}

int main() {
    // Set up vars and file stuff
    int solution = 0;
    FILE *fileptr;
    fileptr = fopen("C:\\Users\\Joey\\Desktop\\advent_of_code_2023_files\\day9_input.txt", "r");
    int numChars = 140;
    int numLines = 200;
    char inLine[numChars];

    long long currLine[50] = {0};
    int numEntries = 0;

    // Loop through the lines of file
    while (fgets(inLine, numChars, fileptr)) {
        //printf("Reading Line...\n");
        int numLevels = 1;
        currLine[numEntries] = strtoll(strtok(inLine, " "), NULL, 10);
        numEntries++;
        while (1){
            char * readIn = strtok(NULL, " ");
            if (readIn == 0) {
                break;
            }
            currLine[numEntries] = strtoll(readIn, NULL, 10);
            numEntries++;
        }
        long long * lastEntry = calloc(numLevels, sizeof(long long));
        *lastEntry = currLine[0];
        while (1) {
            long long * diffTemp = calloc(numEntries - 1, sizeof(long long));
            getDiff(currLine, numEntries, diffTemp);
            numEntries--;
            if (checkDiff(diffTemp, numEntries)) {
                // Loop through numLevels, adding up
                long long tempSolution = 0;
                for (int i = numLevels; i > 0 ; i--) {
                    tempSolution = *(lastEntry + i - 1) - tempSolution;
                }
                solution += tempSolution;
                free(diffTemp);
                break;
            } else {
                numLevels++;
                lastEntry = realloc(lastEntry, numLevels * sizeof(long long));
                *(lastEntry + numLevels - 1) = *(diffTemp);
                memcpy(currLine, diffTemp, numEntries*sizeof(long long));
            }
            free(diffTemp);
        }
        free(lastEntry);
        numEntries = 0;
    }

    printf("Solution is %d\n", solution);

    // Clean up
    fclose(fileptr);
    return 0;
}