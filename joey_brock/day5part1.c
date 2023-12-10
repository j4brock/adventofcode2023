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
    int numSeeds = 20;
    long long seeds[numSeeds];

    int currMapDone = 0;
    enum Map currMap = START;

    long long destRangeStart;
    long long srcRangeStart;
    long long range;

    long long destRangeEnd;
    long long srcRangeEnd;

    long long diff;

    int isSeedChecked[numSeeds];

    // Loop through the rest of the lines of file
    while (fgets(inLine, charBuffer, fileptr)) {

        if (currMap == START) {
            // get the first line which contains the seed numbers
            strtok(inLine, " ");
            for (int i = 0; i < numSeeds; i++) {
                seeds[i] = strtoll(strtok(NULL, " "), NULL, 10);
                isSeedChecked[i] = 0;
            }
            currMap++;
        } else {
            if (isalpha(inLine[0])) {
                for (int i = 0; i < numSeeds; i++) {
                    isSeedChecked[i] = 0;
                }
                //currMap++;
            } else if (isdigit(inLine[0])) {
                destRangeStart = strtoll(strtok(inLine, " "), NULL, 10);
                srcRangeStart = strtoll(strtok(NULL, " "), NULL, 10);
                range = strtoll(strtok(NULL, " "), NULL, 10);
                //destRangeEnd = destRangeStart + range - 1;
                srcRangeEnd = srcRangeStart + range - 1;

                for (int i = 0; i < numSeeds; i++) {
                    if (seeds[i] >= srcRangeStart && seeds[i] <= srcRangeEnd && isSeedChecked[i] == 0) {
                        diff = seeds[i] - srcRangeStart;
                        seeds[i] = destRangeStart + diff;
                        isSeedChecked[i] = 1;
                    }
                }
            }
        }


    }

    long long lowest = 10000000000;
    for (int i = 0; i < numSeeds; i++) {
        if (seeds[i] < lowest) {
            lowest = seeds[i];
        }
    }
    printf("Solution is %d\n", lowest);

    // Clean up
    fclose(fileptr);
    return 0;
}