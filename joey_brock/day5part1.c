#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

enum Map {
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
    fileptr = fopen("C:\\Users\\brockjp1\\Desktop\\test.txt", "r");
    int charBuffer = 75;
    char inLine[charBuffer];
    char seedLine[300];
    int numSeeds = 20;
    long seeds[numSeeds];


    int currMapDone = 0;
    enum Map currMap = SEED_TO_SOIL;
    
    // get the first line which contains the seed numbers
    fgets(seedLine, 300, fileptr);
    strtok(seedLine, " ");
    for (int i = 0; i < numSeeds; i++) {
        seeds[i] = strtol(strtok(NULL, " "), NULL, 10);
    }
    


    // Loop through the rest of the lines of file
    while (fgets(inLine, charBuffer, fileptr)) {

        
    }

    printf("Solution is %d\n", solution);

    // Clean up
    fclose(fileptr);
    return 0;
}