#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


#define HAND_SIZE 5
#define NUM_CARDS 13
#define NUM_HANDS 1000

enum HandType {
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIR,
    THREE_KIND,
    FULL_HOUSE,
    FOUR_KIND,
    FIVE_KIND
};

enum HandType increaseFromJoker(enum HandType hand) {
    switch (hand) {
        case HIGH_CARD:
            return ONE_PAIR;
        case ONE_PAIR:
            return THREE_KIND;
        case TWO_PAIR:
            return FULL_HOUSE;
        case THREE_KIND:
            return FOUR_KIND;
        case FULL_HOUSE:
            return FOUR_KIND;
        case FOUR_KIND:
            return FIVE_KIND;
        default:
            return 0;
    }
}

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
            num = 1;
            break;
        case 'T':
            num = 10;
            break;
        default:
            num = card - '0';
    }
    return num;
}

enum HandType getHandType(const char * hand) {
    int cards[NUM_CARDS] = {0};
    int num, numJokers = 0;
    for (int i = 0; i < HAND_SIZE; i++) {
        num = convertCardToNum(*(hand + i)) - 2;
        if (num >= 0) {
            cards[num]++;
        } else {
            numJokers++;
        }
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

    enum HandType handType;

    if (is5 || numJokers >= 4) {
        return FIVE_KIND;
    } else if (is4) {
        handType = FOUR_KIND;
    } else if (is3 && is2) {
        handType = FULL_HOUSE;
    } else if (is3) {
        handType = THREE_KIND;
    } else if (is2 && numPairs == 2) {
        handType = TWO_PAIR;
    } else if (is2 && numPairs == 1) {
        handType = ONE_PAIR;
    } else {
        handType = HIGH_CARD;
    }
    
    for (int i = 0; i < numJokers; i++) {
        handType = increaseFromJoker(handType);
    }
    return handType;

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
            int card1Num = convertCardToNum(*(hand1Char + i));
            int card2Num = convertCardToNum(*(hand2Char + i));

            if (card1Num > card2Num) {
                return 1;
            } else if (card1Num < card2Num) {
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
    fileptr = fopen("C:\\Users\\brockjp1\\Desktop\\day7_test.txt", "r");
    int numChars = 50;
    //int numLines = 202;
    char inLine[numChars];
    char hand[HAND_SIZE];
    enum HandType currHand;
    char allHands[NUM_HANDS][numChars];
    int handNum = 0;

    // Loop through the lines of file
    while (fgets(inLine, numChars, fileptr)) {
        strcpy(allHands[handNum], inLine);
        handNum++;
    }

    qsort(allHands, NUM_HANDS, sizeof(allHands[0]), compareHands);

    for (int i = 0; i < NUM_HANDS; i++) {
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