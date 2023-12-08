#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <map>
#include <limits.h>
#include <algorithm>


using namespace std;

map<char, int> cards = {{'A', 14} , {'K', 13}, {'Q', 12}, {'J', 1}, {'T', 10}, {'9', 9}, {'8', 8}, {'7', 7}, {'6', 6}, {'5',5}, {'4', 4}, {'3',3}, {'2', 2}};


class PokerHand{

    public:
        map<char, int> cardMap;
        string hand;
        int bet;
        int rank;
        int numJokers = 0;

        PokerHand(const string input){
            hand = input;
            parseHand(hand.substr(0,5));
            bet = stoi(hand.substr(6));
        }

        int getHandValue(){
            if (check5OfKind()){
                return 6;
            } else if (check4OfKind()){
                return 5;
            } else if (checkFullHouse()){
                return 4;
            } else if(check3OfKind()){
                return 3;
            } else if(checkTwoPair()){
                return 2;
            } else if(checkOnePair()){
                return 1;
            } else {
                return 0;
            }
        }

        void toString(){
            for (auto &card : cardMap){
                cout << card.first << ": " << card.second << endl;
            }
            cout << "Bet = " << bet << endl;
        }
    private:

        void parseHand(const string handStr){
            for (auto &ch : handStr){
                //cout << "Adding " << ch << " to map." <<endl;
                if (ch == 'J'){
                    numJokers++;
                } else {
                    if (cardMap.find(ch) != cardMap.end()){
                        cardMap[ch] += 1;
                    } else {
                        cardMap[ch] = 1;
                    }
                }

            }
            cout <<"Num Jokers " << numJokers <<endl;
        }

        bool check5OfKind(){
            for (auto &card : cardMap){
                if (card.second + numJokers  == 5){
                    return true;
                }
            }
            return numJokers == 5;
        }

        bool check4OfKind(){
            for (auto &card : cardMap){
                if (card.second + numJokers == 4){
                    return true;
                }
            }
            return false;
        }

        bool checkFullHouse(){
            int usedJokers = 0;
            bool threeOfKind = false, pair = false; 
            for (auto &card : cardMap){
                if (card.second+numJokers-usedJokers == 3){
                    usedJokers += numJokers;
                    threeOfKind = true;
                } else if (card.second == 2){
                    pair = true;
                }
            }
            return threeOfKind && pair;
        }

        bool check3OfKind(){
            for (auto &card : cardMap){
                if (card.second + numJokers == 3){
                    return true;
                }
            }
            return false;
        }

        bool checkTwoPair(){
            int numPairs = 0;
            for (auto &card : cardMap){
                if (card.second == 2){
                    numPairs++;
                }
            }
            return numPairs == 2;
        }

        bool checkOnePair(){
            for (auto &card : cardMap){
                if (card.second+ numJokers == 2){
                    return true;
                }
            }
            return false;

        }
        
};

bool comparator(const PokerHand& hand1, const PokerHand& hand2) {

    for (int i = 0; i < hand1.hand.size(); i++){
        if(cards[hand1.hand[i]] < cards[hand2.hand[i]]){
            return true;;
        } else if (cards[hand1.hand[i]] > cards[hand2.hand[i]]){
            return false;
        } 
    }
    return false;
}

class HandList{
    public: 
        vector<PokerHand> hands;

        void addHand(PokerHand* hand){
            hands.push_back(*hand);
        }

        vector<PokerHand> sortArr(){
            sort(hands.begin(), hands.end(), &comparator);
            return hands;
        }
};


int main(){

    string file = "inputDay7.txt";
    ifstream inputFile;
    inputFile.open(file);
    string input;
    vector<HandList> gameRanks(7);

    while( getline(inputFile, input)){
        cout << "Game input = " <<  input << endl;
        PokerHand hand(input);
        int value = hand.getHandValue();
        cout << value << endl;
        gameRanks[value].addHand(&hand);
    }

    long betTotal = 0;
    int curRank = 1;
    for (int i = 0; i < gameRanks.size(); i++){
        vector<PokerHand> ranksSorted = gameRanks[i].sortArr();
        for (auto curHand: ranksSorted){
            curHand.toString();
            cout << "Rank = " << curRank << endl;;
            betTotal += curHand.bet*curRank;
            curRank++;
        }
    }
    cout << "Bet Total: " << betTotal << endl;
}