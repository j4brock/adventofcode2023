#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


#define HAND_SIZE 5
#define NUM_CARDS 13

enum HandType {
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIR,
    THREE_KIND,
    FULL_HOUSE,
    FOUR_KIND,
    FIVE_KIND
};

int convertCardToNum(char card) {
    int num;
    switch (card) {
        case 'A':
            num = 14;
            break;
        case 'K':
            num = 13;
            break;
        case 'Q':
            num = 12;
            break;
        case 'J':
            num = 11;
            break;
        case 'T':
            num = 10;
        default:
            num = card - '0';
    }
    return num;
}

enum HandType getHandType(const char * hand) {
    int cards[NUM_CARDS] = {0};
    int num;
    for (int i = 0; i < HAND_SIZE; i++) {
        num = convertCardToNum(*(hand + i)) - 2;
        cards[num]++;
    }

    int is5 = 0, is4 = 0, is3 = 0, is2 = 0, numPairs = 0;
    for (int i = 0; i < NUM_CARDS; i++) {
        switch(cards[i]) {
            case 2:
                is2 = 1;
                numPairs++;
                break;
            case 3:
                is3 = 1;
                break;
            case 4:
                is4 = 1;
                break;
            case 5:
                is5 = 1;
                break;
            default:
                //do nothing!
        }
    }

    if (is5) {
        return FIVE_KIND;
    } else if (is4) {
        return FOUR_KIND;
    } else if (is3 && is2) {
        return FULL_HOUSE;
    } else if (is3) {
        return THREE_KIND;
    } else if (is2 && numPairs == 2) {
        return TWO_PAIR;
    } else if (is2 && numPairs == 1) {
        return ONE_PAIR;
    } else {
        return HIGH_CARD;
    }

}

int compareHands(const void * hand1, const void * hand2) {
    const char * hand1Char = hand1;
    const char * hand2Char = hand2;
    enum HandType hand1Type = getHandType(hand1Char);
    enum HandType hand2Type = getHandType(hand2Char);

    if (hand1Type > hand2Type) {
        return 1;
    } else if (hand2Type > hand1Type) {
        return -1;
    } else {
        for (int i = 0; i < HAND_SIZE; i++) {
            if (convertCardToNum(*(hand1Char + i)) > convertCardToNum(*(hand2Char + i))) {
                return 1;
            } else if (convertCardToNum(*(hand1Char + i)) < convertCardToNum(*(hand2Char + i))) {
                return -1;
            } else {
                // do nothing :)
            }
        }
    }

    return 0;
}

int main() {
    // Set up vars and file stuff
    long long solution = 0;
    FILE *fileptr;
    fileptr = fopen("C:\\Users\\Joey\\Desktop\\advent_of_code_2023_files\\day7_test.txt", "r");
    int numChars = 116;
    int numLines = 202;
    char inLine[numChars + 2];
    char hand[HAND_SIZE];
    enum HandType currHand;
    int numHands = 5;
    char allHands[numHands][11];
    int handNum = 0;

    // Loop through the lines of file
    while (fgets(inLine, numChars, fileptr)) {
        strcpy(allHands[handNum], inLine);
        handNum++;
    }

    qsort(allHands, numHands, sizeof(allHands[0]), compareHands);

    for (int i = 0; i < numHands; i++) {
        strtok(allHands[i], " ");
        int bid = strtoll(strtok(NULL, " "), NULL, 10); 
        int rank = i + 1;
        solution += bid * rank;     
    }

    printf("Solution is %d\n", solution);

    // Clean up
    fclose(fileptr);
    return 0;
}