#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main() {
    // Set up vars and file stuff
    int solution = 0;
    FILE *fileptr;
    fileptr = fopen("C:\\Users\\brockjp1\\Desktop\\test.txt", "r");
    int numChars = 116 + 2; // 116 chars, newline, and terminating char
    int numLines = 202;
    char inLine[numChars];

    int numWinningNums = 10;
    int numMyNums = 25;
    int numCharsPerNum = 3;

    char winningNums[numWinningNums * numCharsPerNum + 1];
    char myNums[numMyNums * numCharsPerNum + 1];

    

    
    int score = 0;
    while (fgets(inLine, numChars, fileptr)) {
        int myNumbers[100] = {0};
        int winningNumbers[numWinningNums];
        int pts = 0;

        strncpy(winningNums, inLine + 9, numWinningNums * numCharsPerNum);
        winningNums[numWinningNums * numCharsPerNum] = '\0';

        strncpy(myNums, inLine + 41, numMyNums * numCharsPerNum);
        myNums[numMyNums * numCharsPerNum] = '\0';

        int numIdx = 0;
        for (int i = 0; i < numMyNums; i++) {
            char temp[4] = {myNums[3*i], myNums[3*i + 1], myNums[3*i + 2], '\0'};
            numIdx = strtol(temp, NULL, 10);
            myNumbers[numIdx] = 1;
        }

        for (int i = 0; i < numWinningNums; i++) {
            char temp[4] = {winningNums[3*i], winningNums[3*i + 1], winningNums[3*i + 2], '\0'};
            //winningNumbers[i] = strtol(temp, NULL, 10);
            numIdx = strtol(temp, NULL, 10);
            if (myNumbers[numIdx]) {
                pts = pts + 1;
            }
        }

        score += (pts == 0)? 0 : pow(2, pts - 1); 
    }

    printf("Solution is %d\n", score);

    // Clean up
    fclose(fileptr);
    return 0;
}