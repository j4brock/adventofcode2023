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
    fileptr = fopen("C:\\Users\\brockjp1\\Desktop\\day8_input.txt", "r");
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

    
    for (int i = 0; i < MAP_SIZE; i++) {

    }


    long long currIdx = 0;
    int currLRIdx = 0;
    int leftOrRight;
    char currIdxChars[3];
    while (currIdx != MAP_SIZE - 1) {
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
        currIdx = map[currIdx][leftOrRight];
        currLRIdx++;
        solution++;
        if (currIdx == 0) {
            break;
        }
    }

    printf("Solution is %d\n", solution);

    // Clean up
    fclose(fileptr);
    return 0;
}