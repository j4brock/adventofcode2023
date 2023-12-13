#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum Direction getOppositionDirection(enum Direction dir) {
    switch (dir) {
        case UP:
            return DOWN;
        case DOWN:
            return UP;
        case LEFT:
            return RIGHT;
        case RIGHT:
            return LEFT;
    }
}

int checkDirection(enum Direction dir, char symbol) {
    // Returns -1 if symbol is start, 1 if symbol represents valid exit, 0 otherwise.

    if (symbol == 'S') {
        return -1;
    }

    switch (dir) {
        case UP:
            return (symbol == '|' || symbol == '7' || symbol == 'F');
        case DOWN:
            return (symbol == '|' || symbol == 'L' || symbol == 'J');
        case LEFT:
            return (symbol == '-' || symbol == 'L' || symbol == 'F');
        case RIGHT:
            return (symbol == '-' || symbol == 'J' || symbol == '7');
    }
}

int main() {
    // Set up vars and file stuff
    int solution = 0;
    FILE *fileptr;
    fileptr = fopen("C:\\Users\\brockjp1\\Desktop\\day10_input.txt", "r");
    int numChars = 140 + 2;
    int numLines = 140;
    char inLine[numChars];

    char map[numLines][numChars];

    int startRow, startCol, lineNum = 0;

    char * startChar;
    // Loop through the lines of file
    while (fgets(inLine, numChars, fileptr)) {
        strcpy(map[lineNum], inLine);
        startChar = strchr(inLine, 'S');
        if (startChar) {
            startRow = lineNum;
            startCol = (int) (startChar - inLine);
        }
        lineNum++;
    }

    //long long * paths[4];
    int startingPathsValid[4] = {0};
    long long pathLengths[4] = {0};
    int colMod[4] = {0, 0, -1, 1};
    int rowMod[4] = {-1, 1, 0, 0};

    if (checkDirection(UP, map[startRow - 1][startCol]) == 1) {
        //paths[UP] = malloc(sizeof(long long));
        startingPathsValid[UP] = 1;
    }
    if (checkDirection(DOWN, map[startRow + 1][startCol]) == 1) {
        //paths[DOWN] = malloc(sizeof(long long));
        startingPathsValid[DOWN] = 1;
    }
    if (checkDirection(LEFT, map[startRow][startCol - 1]) == 1) {
        //paths[LEFT] = malloc(sizeof(long long));
        startingPathsValid[LEFT] = 1;
    }
    if (checkDirection(RIGHT, map[startRow][startCol + 1]) == 1) {
        //paths[RIGHT] = malloc(sizeof(long long));
        startingPathsValid[RIGHT] = 1;
    }

    for (int i = 0; i < 4; i++) {
        if (startingPathsValid[i]){
            enum Direction currDirection = i;
            int currColMod = colMod[i];
            int currRowMod = rowMod[i];
            int currRow = startRow;
            int currCol = startCol;
            int result;
            while (1) {
                result = checkDirection(currDirection, map[currRow + currRowMod][currCol + currColMod]);
                if (result == -1) {
                    break;
                } else if (result == 1) {
                    pathLengths[i]++;
                    currRow += currRowMod;
                    currCol += currColMod;
                    enum Direction oppDirection = getOppositionDirection(currDirection);
                    for (int i = 0; i < 4; i++) {
                        if(checkDirection(i, map[currRow + rowMod[i]][currCol + colMod[i]]) == 1 && oppDirection != i) {
                            currDirection = i;
                            break;
                        }
                    }
                }
            }
        }
    }

    printf("Solution is %d\n", solution);

    // Clean up
    fclose(fileptr);
    return 0;
}