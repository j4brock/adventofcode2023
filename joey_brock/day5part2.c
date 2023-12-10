#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

enum Map {
    START,
    SEED_TO_SOIL,
    SOIL_TO_FERT,
    FERT_TO_WATER,
    WATER_TO_LIGHT,
    LIGHT_TO_TEMP,
    TEMP_TO_HUMID,
    HUMID_TO_LOC
};


int main() {
    // Set up vars and file stuff
    int solution = 0;
    FILE *fileptr;
    fileptr = fopen("C:\\Users\\Joey\\Desktop\\advent_of_code_2023_files\\day5_input.txt", "r");
    int charBuffer = 300;
    char inLine[charBuffer];
    int numSeedInputs = 20;
    long long seedStart[numSeedInputs];
    long long seedRange[numSeedInputs];
    long long numSeeds = 0;
    int currMapDone = 0;
    enum Map currMap = START;

    long long map[8][50][3];
    int numMapEntries[8] = {0};

    long long destRangeStart;
    long long srcRangeStart;
    long long range;

    long long destRangeEnd;
    long long srcRangeEnd;


    long long currSeed;
    long long diff;

    int isSeedChecked[numSeeds];

    fgets(inLine, charBuffer, fileptr);
    strtok(inLine, " ");
    for (int i = 0; i < numSeedInputs/2; i++) {
        seedStart[i] = strtoll(strtok(NULL, " "), NULL, 10);
        seedRange[i] = strtoll(strtok(NULL, " "), NULL, 10);
        numSeeds += seedRange[i];
    }

    // Loop through the rest of the lines of file
    while (fgets(inLine, charBuffer, fileptr)) {

        if (isalpha(inLine[0])) {
            currMap++;
        } else if (isdigit(inLine[0])) {
            map[currMap][numMapEntries[currMap]][0] = strtoll(strtok(inLine, " "), NULL, 10);
            map[currMap][numMapEntries[currMap]][1] = strtoll(strtok(NULL, " "), NULL, 10);
            map[currMap][numMapEntries[currMap]][2] = strtoll(strtok(NULL, " "), NULL, 10);
            numMapEntries[currMap]++;
        }

    }

    long long lowest = 10000000000;
    for (int i = 0; i < numSeedInputs/2; i++) { // Each seed start/range
        for (int j = seedStart[i]; j < seedRange[i]; j++) { // Each individual seed
            currSeed = j;
            for (int k = 1; k < 8; k++) { // Each map
                for (int l = 0; l < numMapEntries[k]; l++) { // Each map entry
                srcRangeStart = map[k][l][1];
                srcRangeEnd = map[k][l][1] + map[k][l][2] - 1;
                destRangeStart = map[k][l][0];
                    if (currSeed >= srcRangeStart && currSeed <= srcRangeEnd) {
                        diff = currSeed - srcRangeStart;
                        currSeed = destRangeStart + diff;
                    }
                }
            }
        }
        if (currSeed < lowest) {
            lowest = currSeed;
        }
    }
/*
    long long lowest = 10000000000;
    for (int i = 0; i < numSeeds; i++) {
        if (seeds[i] < lowest) {
            lowest = seeds[i];
        }
    }
    */
    //printf("Solution is %d\n", lowest);

    // Clean up
    fclose(fileptr);
    return 0;
}