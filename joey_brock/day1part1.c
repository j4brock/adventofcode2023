#include <stdio.h>
#include <ctype.h>

double getTwoDigitNumber(char inLine[], int numChars) {
    int num1 = -1;
    int num2 = -1;
    for (int idx = 0; idx < numChars; idx++) {
        if (isdigit(inLine[idx])) {
            if (num1 == -1) {
                num1 = 10 * (inLine[idx] - '0');
            }
            num2 = inLine[idx] - '0';
        } else if (inLine[idx] == '\n') {
            break;
        }
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
        int temp = getTwoDigitNumber(inLine, bufferSize);
        solution += temp;
    }

    printf("Solution is %d\n", solution);

    // Clean up
    fclose(fileptr);
    return 0;
}