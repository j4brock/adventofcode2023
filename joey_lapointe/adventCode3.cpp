#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctype.h> 


using namespace std;


bool contains(vector<int> row, int x);

class GearRatios{


    public:
        void addPart(int part){
            partNos.push_back(part);
            cout << "Adding part " << part << endl;
            
        }
        int getRatio(){
            if (partNos.size() == 2){
                return partNos[0] * partNos[1];
            }
            return 0; // not enough parts
        }
        int numParts(){
            return partNos.size();
        }

    private:

        vector<int> partNos;


};

vector<char> splitString2CharArray(const string input);
int checkRows(vector<char> rowAbove, vector<char> row, vector<char> rowBelow, bool isFirst, bool isLast);
int getRowDigits(int, vector<char> row);
int convertVectorToInt(vector<int> curNum);
vector<int> getNumber(vector<int> row, int startInd, vector<int>* usedInds);


int main(){


    string file = "inputDay3.txt";
    ifstream inputFile;
    inputFile.open(file);
    string input;

    vector<char> row1, row2, row3;
    if(getline(inputFile, input)){
        row1 = splitString2CharArray(input);
    }
    cout << row1[0] << row1[1] <<row1[2] << row1[3] <<row1.size() << endl;
    if(getline(inputFile, input)){
        row2 = splitString2CharArray(input);
    }

    int sum = checkRows(row1, row1, row2, true, false);
    while(getline(inputFile, input)){
        row3 = splitString2CharArray(input);
        cout << "Line Size " << row3.size() <<endl;

        sum += checkRows(row1, row2, row3, false, false);

        row1 = row2;
        row2 = row3;
    }
    sum += checkRows(row1, row2, row3, false, true);
    cout << sum <<endl;

}


bool contains(vector<int> row, int x){
    for (int i = 0; i < row.size(); i++){
        if (row[i] == x){
            return true;
        }

    }
    return false;
}

vector<int> getNumber(vector<char> row, int startInd, vector<int>* usedInds){
    vector<int> curNum;
    curNum.push_back(row[startInd] - 48);
    cout << row[startInd];

    // check left
    int nextInd = startInd - 1;
    while (nextInd >= 0 && isdigit(row[nextInd]) ){
        cout << row[nextInd];
        usedInds->push_back(nextInd);
        curNum.insert(curNum.begin(), row[nextInd] - 48);
        nextInd--;
    }


    // check right
    nextInd = startInd + 1;
    while (nextInd < row.size() && isdigit(row[nextInd]) ){
        cout << row[nextInd];
        usedInds->push_back(nextInd);
        curNum.push_back(row[nextInd] - 48);
        nextInd++;
    }
    cout <<endl;
    return curNum;

}

int convertVectorToInt(vector<int> curNum){
    int num = 0;
    for (int i = 0; i < curNum.size(); i++){
        num = num*10 + curNum[i];
    }
    return num;
}

bool checkForChar(vector<int> border, vector<char> row){
    for (int i = 0; i < border.size(); i++){
        if ( row[border[i]] != '.' && !isdigit(row[border[i]])){
            cout << "Border value " << border[i] <<endl;
            return true;
        }
    }
    return false;
}

void checkForNum(vector<int> border, vector<char> row, GearRatios* ratio){
    vector<int> usedInds;
    for (int i = 0; i < border.size(); i++){
        if (!contains(usedInds, border[i])){
            usedInds.push_back(border[i]);
            cout << "Checking border " << border[i] << endl;
            if ( isdigit(row[border[i]])){
                ratio->addPart(convertVectorToInt(getNumber(row, border[i], &usedInds)));
                cout << "Border value " << border[i] <<endl;
            }
        }
    }
    
}


int checkRows(vector<char> rowAbove, vector<char> row, vector<char> rowBelow, bool isFirst, bool isLast){
    int sum = 0;
    for (int i = 0; i < row.size(); i++){

        if (row[i] == '*'){
            GearRatios ratio;
            cout << "Gear found at " << i << endl;
            vector<int> border;
            if (i > 0){
                border.push_back(i-1);
            }
            if (i < row.size()-1){
                border.push_back(i+1);
            }
            checkForNum(border, row, &ratio);
            border.push_back(i);
            
            if (!isFirst){
                checkForNum(border, rowAbove, &ratio);
            }
            if (!isLast){
                checkForNum(border, rowBelow, &ratio);
            }
            cout << ratio.numParts() <<endl;
            if (ratio.numParts()> 1){
                cout << "Gear Ratio " << ratio.getRatio() <<endl;
                sum += ratio.getRatio();
            }
        }
    }
    return sum;
}



vector<char> splitString2CharArray(const string input){

    vector<char> row;
    for (int i =0; i < input.length(); i++){
        row.push_back(input[i]);
    }
    return  row;
}