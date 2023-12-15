#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

long long getTaxicabDistance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

int isEmpty(char * test) {
    int k = 0;
    char curr;
    do {
        curr = test[k];
        if (curr == '#') {
            return 0;
        }
        k++;
    } while (curr != '\n' && curr != '\0');
    return 1;
}

int main() {
    // Set up vars and file stuff
    long long solution = 0;
    FILE *fileptr;
    fileptr = fopen("C:\\Users\\brockjp1\\Desktop\\day11_test.txt", "r");
    int numChars = 140 + 2;
    int numLines = 140;
    char inLine[numChars];
    char map[numLines][numChars];

    int numCols = numChars - 2;
    int isLineEmpty[numLines];
    int isColumnEmpty[numCols];

    int galaxyLinePositions[10000];
    int galaxyColumnPosition[10000];
    int numGalaxies = 0;

    for (int k = 0; k < numCols; k++) {
        isColumnEmpty[k] = 1;
    }
    for (int k = 0; k < numLines; k++) {
        isLineEmpty[k] = 1;
    }


    int lineNum = 0;
    // Loop through the lines of file
    while (fgets(inLine, numChars, fileptr)) {
        //strcpy(map[lineNum], inLine);
        for (int k = 0; k < numCols; k++) {
            if (inLine[k] == '#') {     
                galaxyLinePositions[numGalaxies] = lineNum;
                galaxyColumnPosition[numGalaxies] = k;
                if (isLineEmpty[lineNum]) {
                    isLineEmpty[lineNum] = 0;
                }
                if (isColumnEmpty[k]) {
                    isColumnEmpty[k] = 0;
                }
                numGalaxies++;
            }
        }
        lineNum++;
    }

    long long numExpansions = 0;
    for (int i = 0; i < numGalaxies; i++) {
        int thisGalaxyLine = galaxyLinePositions[i];
        int thisGalaxyCol = galaxyColumnPosition[i];
        for (int j = i + 1; j < numGalaxies; j++) {
            int testGalaxyLine = galaxyLinePositions[j];
            int testGalaxyCol = galaxyColumnPosition[j];
            
        
            int startLine;
            int endLine;
            int startCol;
            int endCol;

            if (thisGalaxyLine > testGalaxyLine) {
                startLine = testGalaxyLine;
                endLine = thisGalaxyLine;
            } else {
                startLine = thisGalaxyLine;
                endLine = testGalaxyLine;
            }

            if (thisGalaxyCol > testGalaxyCol) {
                startCol = testGalaxyCol;
                endCol = thisGalaxyCol;
            } else {
                startCol = thisGalaxyCol;
                endCol = testGalaxyCol;
            }

            for (int k = startLine + 1; k < endLine; k++) {
                if (isLineEmpty[k]) {
                    numExpansions++;
                }
            }
            for (int k = startCol + 1; k < endCol; k++) {
                if (isColumnEmpty[k]) {
                    numExpansions++;
                }
            }

            solution += getTaxicabDistance(thisGalaxyLine, thisGalaxyCol, testGalaxyLine, testGalaxyCol);
        }
    }


    printf("Solution is %d\n", solution);
    printf("Expansions: %d\n", numExpansions);

    // Clean up
    fclose(fileptr);
    return 0;
}