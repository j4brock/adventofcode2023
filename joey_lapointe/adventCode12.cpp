#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits.h>
#include <algorithm>
#include <memory>
#include <map>

using namespace std;

const string file = "inputDay12.txt";
class Springs;
vector<int> parseNumbers(string numbers);
vector<Springs> findCombinations(Springs gear, map<string, int>& cache);


class Springs{

    public:
        string gearList;
        vector<int> gearRecord;
        vector<int> damagedInds;
        vector<int> unknownInds;
        bool matches = true;
        int totalBroken;
        int curBroken = 0;

        Springs(string gear, vector<int> record, int broken){
            gearList = gear;
            gearRecord = record;
            int indGear = 0;
            totalBroken = broken;

            int numContinuous = 0;
            int indRecord = 0;

            for (char &ch : gearList){
                if (ch == '#') {
                    damagedInds.push_back(indGear);
                    curBroken++;
                    numContinuous++;

                } else {
                    if(ch == '?'){
                        unknownInds.push_back(indGear);
                    }
                    if (numContinuous > 0 && gearRecord[indRecord++] != numContinuous){
                        matches = false;
                    }
                    numContinuous = 0;
                }
                indGear++;
            }
            if (numContinuous > 0 && gearRecord[indRecord++] != numContinuous){
                        matches = false;
            }
            if (indRecord != gearRecord.size()){
                matches = false;
            }

        }
};

int main(){

    ifstream inputFile;
    inputFile.open(file);
    string input;

    int sumCombinations = 0;
    int count = 0;
    while(getline(inputFile, input)){

        string gears = input.substr(0, input.find(" "));
        string numbers = input.substr(input.find(" ")+1);
        vector<int> record = parseNumbers(numbers);
        int recordSum = 0;
        for (auto i : record){
            recordSum += i;
        }

        Springs spring(gears, record, recordSum);

        map<string, int> cache;
        cache[spring.gearList] = 1;
        vector<Springs> possibleCombs = findCombinations(spring, cache);
        sumCombinations += possibleCombs.size();
        if (count++ % 10 == 0){
            cout << count/10 << "%" << endl;
        }
    }

    cout << "Possible Combinations " << sumCombinations << endl;


}

vector<int> parseNumbers(string numbers){
    vector<int> nums;
    for( auto &ch : numbers){
        if (ch != ','){
            nums.push_back(int(ch) - 48);
        }
    }
    return nums;
}

vector<Springs> findCombinations(Springs gear, map<string, int>& cache){
    vector<Springs> springs;

    // check if matches condition

    if (gear.matches){
        springs.push_back(gear);
        return springs;
    } else if(gear.curBroken >= gear.totalBroken){
        return springs;
    } else {
        // generate

        for (int indQ : gear.unknownInds){
            string newGearString = gear.gearList;
            newGearString[indQ] = '#';
            Springs newGear(newGearString, gear.gearRecord, gear.totalBroken);
            if (cache.find(newGearString) == cache.end()){
                cache[newGearString] = 1;
                vector<Springs> newSprings = findCombinations(newGear, cache);
                springs.insert(springs.end(), newSprings.begin(), newSprings.end());
            } 
        }
    }


    return springs;
}
