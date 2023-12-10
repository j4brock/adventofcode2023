#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

long long appendNums(long long left, long long right) {
    int numDigitsLeft = printf("%d", left);
    int numDigitsRight = printf("%d", right);

    return (pow(10, numDigitsRight) * left) + right; 
}

int main() {
    // Set up vars and file stuff
    int solution = 1;
    FILE *fileptr;
    fileptr = fopen("C:\\Users\\Joey\\Desktop\\advent_of_code_2023_files\\day6_input.txt", "r");
    int numChars = 40;
    char inLine[numChars + 2];
    int numRaces = 4;
    long long inNum1; 
    long long inNum2;
    long long time;
    long long distance;

    fgets(inLine, numChars, fileptr);
    strtok(inLine, " ");

    inNum1 = strtol(strtok(NULL, " "), NULL, 10);
    inNum2 = strtol(strtok(NULL, " "), NULL, 10);
    time = appendNums(inNum1, inNum2);

    inNum1 = strtol(strtok(NULL, " "), NULL, 10);
    time = appendNums(time, inNum1);
    inNum2 = strtol(strtok(NULL, " "), NULL, 10);
    time = appendNums(time, inNum2);




    

    fgets(inLine, numChars, fileptr);
    strtok(inLine, " ");

    inNum1 = strtol(strtok(NULL, " "), NULL, 10);
    inNum2 = strtol(strtok(NULL, " "), NULL, 10);
    distance = appendNums(inNum1, inNum2);

    inNum1 = strtol(strtok(NULL, " "), NULL, 10);
    distance = appendNums(distance, inNum1);
    inNum2 = strtol(strtok(NULL, " "), NULL, 10);
    distance = appendNums(distance, inNum2);



    long long timeToRun;
    long long distanceRan;
    int numWaysToWin = 0;
    for (long long j = 1; j < time - 1; j++) { // Loop through each (useful) button down time
        // j is speed
        timeToRun = time - j;
        distanceRan = timeToRun * j;
        if (distanceRan > distance) {
            numWaysToWin++;
        }
    }
    solution = numWaysToWin;
    
    
    printf("Solution is %d\n", solution);

    // Clean up
    fclose(fileptr);
    return 0;
}