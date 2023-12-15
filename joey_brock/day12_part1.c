#include <stdio.h>
#include <ctype.h>

int main() {
    // Set up vars and file stuff
    int solution = 0;
    FILE *fileptr;
    fileptr = fopen("C:\\Users\\brockjp1\\Desktop\\day12_test.txt", "r");
    int numChars = 50;
    int numLines = 1000;
    char inLine[numChars + 2];

    // Loop through the lines of file
    while (fgets(inLine, numChars, fileptr)) {

    }

    printf("Solution is %d\n", solution);

    // Clean up
    fclose(fileptr);
    return 0;
}