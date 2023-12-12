#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#define MAP_SIZE 17576

long long convertCharsToIdx(char * chars) {
    long long digits[3];
    for (int i = 0; i < 3; i++) {
        digits[i] = *(chars + i) - 'A';
    }
    long long dig1 = (pow(26, 2))*digits[0];
    long long dig2 = (26)*digits[1];
    long long dig3 = digits[2];
    long long answer = dig1 + dig2 + dig3;
    return answer;
}

// Made this for testing purposes
void convertIdxToChar(long long idx, char * answer) {
    char firstChar = 'A' + idx/(26 * 26);
    idx = idx % (26 * 26);
    char secondChar = 'A' + idx/26;
    idx = idx % 26;
    char thirdChar = 'A' + idx;

    answer[0] = firstChar;
    answer[1] = secondChar;
    answer[2] = thirdChar;
    answer[3] = '\0';   
}

int main() {
    // Set up vars and file stuff
    int solution = 0;
    FILE *fileptr;
    fileptr = fopen("C:\\Users\\Joey\\Desktop\\advent_of_code_2023_files\\day8_input.txt", "r");
    int numLRChars = 265;
    int numDirChars = 20;
    int numDirLines = 770;
    char lrLine[numLRChars];
    char inLine[numDirChars];

    long long map[MAP_SIZE][2] = {0};

    fgets(lrLine, numLRChars, fileptr);
    fgets(NULL, numLRChars, fileptr);

    int dirLine = 0;
    long long mapIdx;
    long long leftIdx, rightIdx;

    // Loop through the lines of file
    while (fgets(inLine, numDirChars, fileptr)) {
        if (inLine[0] != '\n') {
            mapIdx = convertCharsToIdx(inLine);
            leftIdx = convertCharsToIdx(inLine + 7);
            rightIdx = convertCharsToIdx(inLine + 12);
            map[mapIdx][0] = leftIdx;
            map[mapIdx][1] = rightIdx;
        }
    }
    char testing[4];
    long long maxStartingPositions = 26*26;
    long long actualStartingPositions = 0;
    long long startingPositions[maxStartingPositions];
    for (int i = 0; i < MAP_SIZE; i = i + 26) {
        if (map[i][0] == 0 && map[i][1] == 0) {
            // Do nothing
        } else {
            startingPositions[actualStartingPositions] = i;
            actualStartingPositions++;
        }
    }

    long long * currIdx = calloc(actualStartingPositions, sizeof(long long));
    for (int i = 0; i < actualStartingPositions; i++) {
        *(currIdx + i) = startingPositions[i];
    }
    int currLRIdx = 0;
    int leftOrRight;

    printf("Starting search...\n");
    while (1) {
        switch (lrLine[currLRIdx]) {
            case 'L':
                leftOrRight = 0;
                break;
            case 'R':
                leftOrRight = 1;
                break;
            case '\n':
                currLRIdx = 0;
                continue;
            default:
                // Shouldn't get here
        }

        int allDone = 1;
        int allZeros = 1;
        long long doneIdx = convertCharsToIdx("ZZZ");
        long long startIdx = 0;
        for (int i = 0; i < actualStartingPositions; i++) {
            //convertIdxToChar(*(currIdx + i), testing);
            //printf("%d: %s   ", i, testing);
            *(currIdx + i) = map[*(currIdx + i)][leftOrRight];
            allDone = allDone && (*(currIdx + i) == doneIdx);
            allZeros = allZeros && (*(currIdx + i) == 0);
        }
        if (allDone) {
            printf("DONE\n");
            break;
        } else if (allZeros || *currIdx == 0) {
            printf("You're in a loop!\n");
            break;
        }
        currLRIdx++;
        solution++;
    }
    free(currIdx);
    printf("Solution is %d\n", solution);

    // Clean up
    fclose(fileptr);
    return 0;
}