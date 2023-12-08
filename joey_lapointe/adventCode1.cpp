#include <iostream>
#include <string>
#include <ctype.h>
#include <fstream>
#include <limits.h>

using namespace std;
int getNumberFromLine(const string input);

std::string numbers[9]
      = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int main()
{
    string file = "input1.txt";
    ifstream inputFile;
    inputFile.open(file);
    string input;
    int sum = 0;

    if (inputFile.is_open()){
        while( getline(inputFile, input)){
            int combined = getNumberFromLine(input);
            sum += combined;
        }
    }

    
    cout << sum << endl;

}

int getNumberFromLine(string input){

    int firstNum = -1, firstInd = INT_MAX, lastNum = -1, lastInd = -1;
    bool firstPass = true;
    int count = 0;
    string::iterator it;

    for (it = input.begin(); it != input.end(); it++){
        if (isdigit(*it)){
            int digit = *it - '0';
            if (firstPass){
                firstNum = digit;
                firstInd = count;
                firstPass = false;
            }
            lastNum = digit;
            lastInd = count;
        }
        count++;
    }

    for (int i = 1; i <= 9; i++){

        string numStr = numbers[i-1];
        int indexStr = input.find(numStr);

        if (indexStr != -1){
            if (indexStr < firstInd){
                firstInd = indexStr;
                firstNum = i;
            }
        }

        indexStr = input.rfind(numStr);


        if (indexStr != -1){
            if (indexStr > lastInd){
                lastInd = indexStr;
                lastNum = i;
            }
        }



    }

    int combined = 0;
    if (firstNum != -1 && lastNum != -1){
        combined = 10*firstNum + lastNum;
    }    
    cout << combined << endl;
    return combined;
}
