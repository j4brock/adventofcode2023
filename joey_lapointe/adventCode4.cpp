#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

int getPointsForCard(const string input);

int main(){
    string file = "inputDay4.txt";
    ifstream inputFile;
    inputFile.open(file);
    string input;
    int numWins = 0;
    int gameId = 1;
    int sum = 0;
    int numCopies[205];
    for (int indCopies = 0; indCopies < 205; indCopies++){
        numCopies[indCopies] = 1;
    }

    if (inputFile.is_open()){
        while( getline(inputFile, input)){

            int numMatches = getPointsForCard(input);
            cout << "Game " << gameId << " = " << numMatches << endl;
            for (int i = 0; i < numMatches; i++){
                numCopies[gameId+i] += numCopies[gameId-1];
            }    
            sum += numCopies[gameId -1];
            cout << "Num Copies = " << numCopies[gameId -1] <<endl;
            gameId++;
        }
    }


    cout << sum << endl;
}

vector<int> splitString2Array(const string numbersStr){

    vector<int> numbers;
    bool numUpdated = false;
    int numIndex = 0;
    numbers.push_back(0);
    for (int i =0; i < numbersStr.length(); i++){
        if (numbersStr[i] == ' '){
            if (numUpdated){
                numIndex++;
                numbers.push_back(0);
                numUpdated = false;
            }
        } else {
            int num = (numbersStr[i] - 48);
            numbers[numIndex] = numbers[numIndex]*10 + num;
            numUpdated = true;
        }
    }
    return  numbers;
}

int getPointsForCard(const string input){

    int gameId, numMatches = 0; 
    vector<int> winnningNumbers;
    vector<int> gameNumbers;


    gameId = stoi(input.substr(input.find(" "), input.find(":")));
    cout << "Game ID: " << gameId << endl;

    int substringLength = input.find('|') - input.find(':') -2;
    string winningNumbersStr = input.substr(input.find(':')+2, substringLength); // '|' index is 23
    cout << winningNumbersStr << "|" << endl;
    winnningNumbers = splitString2Array(winningNumbersStr);

    cout << "Winning numbers: " << winnningNumbers.size() << endl;

    string gameNumbersStr = input.substr(input.find("|")+1);
    gameNumbers = splitString2Array(gameNumbersStr);
    cout << gameNumbersStr << "|" <<endl;

    cout << "Game numbers: " << gameNumbers.size() << endl;


    for (int i = 0; i < winnningNumbers.size(); i++){
        for (int j = 0; j< gameNumbers.size(); j++){
            if (winnningNumbers[i] == gameNumbers[j]){
                cout << gameNumbers[j] << endl;
                numMatches++;
            }
        }
    }

    return numMatches;
}