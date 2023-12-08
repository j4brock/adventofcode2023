#include <stdio.h>
#include <ctype.h>
#include <math.h>

int main() {
    // Set up vars and file stuff
    int numLines = 140;
    int numChars = 140;
    int solution = 0;
    FILE *fileptr;
    //fileptr = fopen("C:\\Users\\Joey\\Desktop\\advent_of_code_2023_files\\day3_input.txt", "r");
    fileptr = fopen("C:\\Users\\brockjp1\\Desktop\\test.txt", "r");
    char inLine[numChars];

    char schematic[numLines][numChars];
    int lineIdx = 0;
    // Load input file into a 2d array
    while (fgets(inLine, numChars + 2, fileptr)) { // Need to add +2 for newline and terminating char?
        for (int charIdx = 0; charIdx < numChars; charIdx++) {
            schematic[lineIdx][charIdx] = inLine[charIdx];
        }
        lineIdx++;
    }

    int tempNum = 0;
    int kTemp;
    int kStart;
    int kEnd;
    int multiplier = 0;
    // Loop through schematic, looking for symbols. Then find all adjacent numbers
    for (int i = 1; i < numLines; i++) {
        for (int k = 0; k < numChars; k++) {
            if (schematic[i][k] == '.') {
                printf("%c", schematic[i][k]);
                continue; // best keyword in all of programming
            }
            printf("%c", schematic[i][k]);
            if (isalpha(schematic[i][k]) == 0 && isdigit(schematic[i][k]) == 0) {
                // we have a symbol!
                // first check to the left:
                if (k > 0) {
                    if (isdigit(schematic[i][k-1]) > 0) {
                        kEnd = k-1;
                        kStart = k-1;
                        while(isdigit(schematic[i][kStart]) > 0 && kStart >= 0) {
                            kStart--;
                        }
                        multiplier = 0;
                        for (int kTemp = kEnd; kTemp > kStart; kTemp--) {
                            tempNum = tempNum + (pow(10.0, multiplier))*(schematic[i][kTemp] - '0');
                            multiplier++;
                            schematic[i][kTemp] = '.'; // don't want to double count
                        }
                        solution += tempNum;
                        tempNum = 0;
                    }
                    
                }

                // now let's check to the right
                if (k < numChars - 1) {
                    if (isdigit(schematic[i][k+1]) > 0) {
                        kEnd = k+1;
                        kStart = k+1;
                        while(isdigit(schematic[i][kEnd]) > 0 && kEnd < numChars) {
                            kEnd++;
                        }
                        multiplier = 0;
                        for (int kTemp = kEnd - 1; kTemp >= kStart; kTemp--) {
                            tempNum = tempNum + (pow(10.0, multiplier))*(schematic[i][kTemp] - '0');
                            multiplier++;
                            schematic[i][kTemp] = '.'; // don't want to double count
                        } 
                        solution += tempNum;
                        tempNum = 0;
                    }
                    
                }

                // now check up
                if (i > 0) {
                    if (isdigit(schematic[i - 1][k]) > 0) {
                        kStart = k;
                        kEnd = k;
                        while(isdigit(schematic[i - 1][kStart]) > 0 && kStart >= 0) {
                            kStart--;
                        }
                        while(isdigit(schematic[i - 1][kEnd]) > 0 && kEnd < numChars) {
                            kEnd++;
                        }
                        multiplier = 0;
                        for (int kTemp = kEnd - 1; kTemp > kStart; kTemp--) {
                            tempNum = tempNum + (pow(10.0, multiplier))*(schematic[i - 1][kTemp] - '0');
                            multiplier++;
                            schematic[i - 1][kTemp] = '.'; // don't want to double count
                        } 
                        solution += tempNum;
                        tempNum = 0;
                    }

                    // now check up left
                    if (k > 0){
                        if (isdigit(schematic[i - 1][k - 1]) > 0) {
                            kStart = k - 1;
                            kEnd = k - 1;
                            while(isdigit(schematic[i - 1][kStart]) > 0 && kStart >= 0) {
                                kStart--;
                            }
                            while(isdigit(schematic[i - 1][kEnd]) > 0 && kEnd < numChars) {
                                kEnd++;
                            }
                            multiplier = 0;
                            for (int kTemp = kEnd - 1; kTemp > kStart; kTemp--) {
                                tempNum = tempNum + (pow(10.0, multiplier))*(schematic[i - 1][kTemp] - '0');
                                multiplier++;
                                schematic[i - 1][kTemp] = '.'; // don't want to double count
                            } 
                            solution += tempNum;
                            tempNum = 0;
                        }
                    }

                    // now check up right
                    if (k < numChars - 1){
                        if (isdigit(schematic[i - 1][k + 1]) > 0) {
                            kStart = k + 1;
                            kEnd = k + 1;
                            while(isdigit(schematic[i - 1][kStart]) > 0 && kStart >= 0) {
                                kStart--;
                            }
                            while(isdigit(schematic[i - 1][kEnd]) > 0 && kEnd < numChars) {
                                kEnd++;
                            }
                            multiplier = 0;
                            for (int kTemp = kEnd - 1; kTemp > kStart; kTemp--) {
                                tempNum = tempNum + (pow(10.0, multiplier))*(schematic[i - 1][kTemp] - '0');
                                multiplier++;
                                schematic[i - 1][kTemp] = '.'; // don't want to double count
                            } 
                            solution += tempNum;
                            tempNum = 0;
                        }
                    }
                }

                // now check down
                if (i < (numLines - 1)) {
                    if (isdigit(schematic[i + 1][k]) > 0) {
                        kStart = k;
                        kEnd = k;
                        while(isdigit(schematic[i + 1][kStart]) > 0 && kStart >= 0) {
                            kStart--;
                        }
                        while(isdigit(schematic[i + 1][kEnd]) > 0 && kEnd < numChars) {
                            kEnd++;
                        }
                        multiplier = 0;
                        for (int kTemp = kEnd - 1; kTemp > kStart; kTemp--) {
                            tempNum = tempNum + (pow(10.0, multiplier))*(schematic[i + 1][kTemp] - '0');
                            multiplier++;
                            schematic[i + 1][kTemp] = '.'; // don't want to double count
                        } 
                        solution += tempNum;
                        tempNum = 0;
                    }

                    // now check down left
                    if (k > 0){
                        if (isdigit(schematic[i + 1][k - 1]) > 0) {
                            kStart = k - 1;
                            kEnd = k - 1;
                            while(isdigit(schematic[i + 1][kStart]) > 0 && kStart >= 0) {
                                kStart--;
                            }
                            while(isdigit(schematic[i + 1][kEnd]) > 0 && kEnd < numChars) {
                                kEnd++;
                            }
                            multiplier = 0;
                            for (int kTemp = kEnd - 1; kTemp > kStart; kTemp--) {
                                tempNum = tempNum + (pow(10.0, multiplier))*(schematic[i + 1][kTemp] - '0');
                                multiplier++;
                                schematic[i + 1][kTemp] = '.'; // don't want to double count
                            } 
                            solution += tempNum;
                            tempNum = 0;
                        }
                    }

                    // now check down right
                    if (k < numChars - 1){
                        if (isdigit(schematic[i + 1][k + 1]) > 0) {
                            kStart = k + 1;
                            kEnd = k + 1;
                            while(isdigit(schematic[i + 1][kStart]) > 0 && kStart >= 0) {
                                kStart--;
                            }
                            while(isdigit(schematic[i + 1][kEnd]) > 0 && kEnd < numChars) {
                                kEnd++;
                            }
                            multiplier = 0;
                            for (int kTemp = kEnd - 1; kTemp > kStart; kTemp--) {
                                tempNum = tempNum + (pow(10.0, multiplier))*(schematic[i + 1][kTemp] - '0');
                                multiplier++;
                                schematic[i + 1][kTemp] = '.'; // don't want to double count
                            } 
                            solution += tempNum;
                            tempNum = 0;
                        }
                    }
                }
            }
        }
    }

    

    printf("Solution is %d\n", solution);

    // Clean up
    fclose(fileptr);
    return 0;
}