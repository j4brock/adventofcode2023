#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits.h>
#include <algorithm>
#include <set>

using namespace std;


class GalaxyMap{

    public:

        //vector<vector<char>> galaxyMap;
        vector<pair<long long, long long>> galaxies;

        void addToMap(string line){
            colSize = line.size();
            vector<char> curRow = * new vector<char>;
            bool emptyRow = true; // no galaxies in row;
            for (int i = 0; i < line.size(); i++){
                curRow.push_back(line[i]);
                if(line[i] == '#'){
                    galaxies.push_back(* new pair(numRows, i));
                    emptyRow = false;
                    colsWithGalaxy.insert(i);
                }
            }

            if (emptyRow){
                numRows+= expansionFactor;
            } else {
                numRows++;
            }
        }

        void checkEmptyRows(){
            set<long long> colInds;
            set<long long> emptyCols;

            for (long long i = 0; i < colSize; ++i)
            {
                if (colsWithGalaxy.find(i) == colsWithGalaxy.end()){
                    emptyCols.insert(i);
                }
            }
            set<long long>::iterator it;
            long long colAdjust = 0; // need to adjust for expansion
            for (it = emptyCols.begin(); it != emptyCols.end(); it++){
                long long colInd = *it;
                for (auto & coord : galaxies){
                    if (coord.second > colInd + colAdjust*(expansionFactor-1)){
                        coord.second += (expansionFactor-1);
                    }
                }
                colAdjust++;
            }
        }

        long long findAllDistances(pair<long long,long long> coord1, pair<long long,long long> coord2){
            return abs(coord1.first - coord2.first) + abs(coord1.second - coord2.second);
        }

        long long findAllDistances(){
            long long sum = 0;
            for (int i = 0; i < galaxies.size(); i++){
                for (int j = i; j < galaxies.size(); j++){
                    sum += findAllDistances(galaxies[i], galaxies[j]);
                }
            }
            return sum;
        }

    private:
        long long numRows = 0;
        long long colSize;
        set<long long> colsWithGalaxy;
        long long expansionFactor = 1000000;
};

int main(){

    string file = "inputDay11.txt";
    ifstream inputFile;
    inputFile.open(file);
    string input;
    GalaxyMap galaxyMap;

    // build matrix
    while (getline(inputFile, input)){
        galaxyMap.addToMap(input);

    } 
    galaxyMap.checkEmptyRows();

    long long dist = galaxyMap.findAllDistances();

    cout << "Combined Dist " << dist << endl;

}

