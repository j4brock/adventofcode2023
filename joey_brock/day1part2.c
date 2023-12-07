#include <stdio.h>
#include <ctype.h>
#include <string.h>


int checkLettersForNumbers(char inLine[], int startIdx) {
    if (inLine[startIdx] == 'o' & inLine[startIdx + 1] == 'n' & inLine[startIdx + 2] == 'e') {
        return 1;
    }
    
    if (inLine[startIdx] == 't' & inLine[startIdx + 1] == 'w' & inLine[startIdx + 2] == 'o') {
        return 2;
    }

    if (inLine[startIdx] == 't' & inLine[startIdx + 1] == 'h' & inLine[startIdx + 2] == 'r' & inLine[startIdx + 3] == 'e' & inLine[startIdx + 4] == 'e') {
        return 3;
    }

    if (inLine[startIdx] == 'f' & inLine[startIdx + 1] == 'o' & inLine[startIdx + 2] == 'u' & inLine[startIdx + 3] == 'r') {
        return 4;
    }

    if (inLine[startIdx] == 'f' & inLine[startIdx + 1] == 'i' & inLine[startIdx + 2] == 'v' & inLine[startIdx + 3] == 'e') {
        return 5;
    }
    
    if (inLine[startIdx] == 's' & inLine[startIdx + 1] == 'i' & inLine[startIdx + 2] == 'x') {
        return 6;
    }

    if (inLine[startIdx] == 's' & inLine[startIdx + 1] == 'e' & inLine[startIdx + 2] == 'v' & inLine[startIdx + 3] == 'e' & inLine[startIdx + 4] == 'n') {
        return 7;
    }

    if (inLine[startIdx] == 'e' & inLine[startIdx + 1] == 'i' & inLine[startIdx + 2] == 'g' & inLine[startIdx + 3] == 'h' & inLine[startIdx + 4] == 't') {
        return 8;
    }
    
    if (inLine[startIdx] == 'n' & inLine[startIdx + 1] == 'i' & inLine[startIdx + 2] == 'n' & inLine[startIdx + 3] == 'e') {
        return 9;
    }

    return -1;
}


int getTwoDigitNumber(char inLine[], int numChars) {
    int num1 = -1;
    int num2 = -1;
    int num2Temp = -1;
    for (int idx = 0; idx < numChars; idx++) {
        if (isdigit(inLine[idx])) {
            if (num1 == -1) {
                num1 = 10 * (inLine[idx] - '0');
            }
            num2 = inLine[idx] - '0';
        } else if (inLine[idx] == '\n') {
            break;
        } else {
            if (num1 == -1) {
                num1 = checkLettersForNumbers(inLine, idx);
                if (num1 > 0) {
                    num1 *= 10;
                }
            } else {
                num2Temp = checkLettersForNumbers(inLine, idx);
                if (num2Temp > 0) {
                    num2 = num2Temp;
                }
                
            }
        }
        
    }

    if (num2 == -1) {
        num2 = num1 / 10;
    }

    printf("%s\n", inLine);
    printf("num1: %d, num2: %d\n", num1, num2);
    return num1 + num2;

}



int main() {
    // Set up vars and file stuff
    int solution = 0;
    FILE *fileptr;
    fileptr = fopen("C:\\Users\\Joey\\Desktop\\advent_of_code_2023_files\\day1_input.txt", "r");
    int bufferSize = 100;
    char inLine[bufferSize];

    // Loop through the lines, adding up the solution numbers
    while (fgets(inLine, bufferSize, fileptr)) {
        //int numChars = sizeof(inLine)/sizeof(inLine[0]);
        int temp = getTwoDigitNumber(inLine, strlen(inLine));
        solution += temp;
    }

    printf("Solution is %d\n", solution);

    // Clean up
    fclose(fileptr);
    return 0;
}