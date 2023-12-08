#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <map>
#include <limits.h>
typedef unsigned long long ulong;
using namespace std;



class SeedMap{
    public:
        vector<vector<ulong>> spans;

        void addSpan(vector<ulong> span){
            spans.push_back(span);
        }

        ulong getValue(ulong key){
            ulong value = key;
            for (int indSpan = 0; indSpan < spans.size(); indSpan++){
                ulong source = spans[indSpan][1];
                ulong length = spans[indSpan][2];
                if (key >= source && key < source + length){
                    ulong diff = key - source;
                    return  spans[indSpan][0] + diff;
                }
            }
            return key;
        }

        ulong getRange(ulong key){
            ulong closestRange = LONG_LONG_MAX;
            int indClosest = 0;
            for (int indSpan = 0; indSpan < spans.size(); indSpan++){
                ulong source = spans[indSpan][1];
                ulong length = spans[indSpan][2];
                if (key >= source && key < source + length){
                    return  source + length - key;
                } else if(key < source) {
                    if (source - key < closestRange){
                        indClosest = indSpan;
                        closestRange = source - key;
                    }
                }
            
                
            }
            return closestRange;
 
        }
    
};

vector<ulong> splitString2Array(const string numbersStr);
SeedMap readMap(ifstream* inputFile);

int main(){

    SeedMap seedToSoil;
    SeedMap soilToFertilizer;
    SeedMap fertilizerToWater;
    SeedMap waterToLight;
    SeedMap lightToTemp;
    SeedMap tempToHumidity;
    SeedMap humidityToLocation;
    vector<SeedMap> maps = {seedToSoil, soilToFertilizer, fertilizerToWater, waterToLight, lightToTemp, tempToHumidity, humidityToLocation};
    
    string file = "inputDay5.txt";
    ifstream inputFile;
    inputFile.open(file);
    string input;
    vector<ulong> seeds;
    int mapInd = 0;
    // read first line
    if (inputFile.is_open()){

        if(getline(inputFile, input)){
            seeds = splitString2Array(input.substr(input.find(" ") + 1));
        }
        cout << seeds[0] << "," << seeds[1] << " size " << seeds.size() << endl;

        while( getline(inputFile, input)){
            if (input.empty()){
                continue; // skip empty line
            } else {
                cout << "Mapping " << mapInd << endl;
                maps[mapInd] = readMap(&inputFile);
                mapInd++;
            }


        }
    }
    ulong minLocation = LONG_MAX;
    for (int indSeed = 0; indSeed < seeds.size(); indSeed += 2){
        cout << "Ind Seed " << indSeed << endl;
        ulong key = seeds[indSeed];
        ulong endKey = key + seeds[indSeed+1];
        while(key < endKey){
            ulong value = key;
            ulong range = 0, minRange = LONG_MAX;
            for (int indMap = 0; indMap < maps.size(); indMap++){
                SeedMap curMap = maps[indMap];
                range = curMap.getRange(value);
                value = curMap.getValue(value);
                if (range < minRange){
                    minRange = range;
                }
            }



            //cout << "Seed " << key << " = Location " << value << endl;
            if (minLocation > value){
                minLocation = value;
            }
            cout << minRange << endl;
            key = key += minRange;
        }   
    }
    cout << "Min Location = " << minLocation << endl;


}

SeedMap readMap(ifstream* inputFile){
    SeedMap seedMap;
    string input;

    while( getline(*inputFile, input)){
        if (input.empty()){
            break;
        }
        vector<ulong> values = splitString2Array(input);
        seedMap.addSpan(values);
    }
    return seedMap;
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
            ulong num = (numbersStr[i] - 48);
            numbers[numIndex] = numbers[numIndex]*10 + num;
            numUpdated = true;
        }
    }
    return  numbers;
}
