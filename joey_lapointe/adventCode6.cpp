#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;
typedef unsigned long long ulong;

vector<ulong> splitString2Array(const string numbersStr);


int main(){

    string file = "inputDay6.txt";
    ifstream inputFile;
    inputFile.open(file);
    string input;
    // first read time
    vector<ulong> time;

    if(getline(inputFile, input)){
        time = splitString2Array(input.substr(input.find(" ")));
    }   

    // then read Distance
    vector<ulong> distRecord;
    if(getline(inputFile, input)){
        distRecord = splitString2Array(input.substr(input.find(" ")));
    }  

    int numCombinations = 1;
    for (int ind = 0; ind < time.size(); ind++){
        ulong timeAcel = 1;
        ulong timeGo, dist;
        bool foundWin = false;
        ulong firstWin = 0;
        ulong numWins = 0;
        while (timeAcel < time[ind] && !foundWin){
            timeGo = time[ind] - timeAcel;
            dist = timeAcel * timeGo;
            //cout << timeAcel << " " << timeGo << " "  << dist << endl;
            if (dist > distRecord[ind]){
                firstWin = timeAcel;
                foundWin = true;
            }
            timeAcel++;
        }
        if (foundWin){
            numWins = time[ind] - 2*firstWin + 1;
            cout << "Num Wins: " << numWins << " first win " << firstWin << endl;
            numCombinations *= numWins;
        }
    }
    cout << numCombinations << endl;


}


vector<ulong> splitString2Array(const string numbersStr){

    vector<ulong> numbers;
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


