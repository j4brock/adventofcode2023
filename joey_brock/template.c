#include <stdio.h>
#include <ctype.h>

int main() {
    // Set up vars and file stuff
    int solution = 0;
    FILE *fileptr;
    fileptr = fopen("C:\\Users\\Joey\\Desktop\\advent_of_code_2023_files\\day1_input.txt", "r");
    int numChars = 116;
    int numLines = 202;
    char inLine[numChars + 2];

    // Loop through the lines, adding up the solution numbers
    while (fgets(inLine, numChars, fileptr)) {

    }

    printf("Solution is %d\n", solution);

    // Clean up
    fclose(fileptr);
    return 0;
}