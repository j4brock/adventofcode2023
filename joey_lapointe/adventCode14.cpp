#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits.h>
#include <algorithm>
#include <set>
#include <chrono>

#include <memory>

using namespace std;
class Rocks;
const string file = "inputDay14.txt";
void spinCycle(vector<vector<int>>& rockMap, vector<Rocks>& rocks);


class Rocks{

    public:
        bool isFixed;
        int row;
        int col;

        Rocks(int r, int c, bool fixed){
            row = r;
            col = c;
            isFixed = fixed;
        }
};

int main(){

    auto start = chrono::high_resolution_clock::now();

    ifstream inputFile;
    inputFile.open(file);
    string input;

    
    vector<vector<int>> rockMap; // only the rolling rocks
    vector<Rocks> rocks; // list of last fixed rock in each column

    int numRows = 0, rockInd = 0;
    while( getline(inputFile, input)){
        vector<int> mapRow;
        for (int indCol = 0; indCol < input.size(); indCol++){
            if (input[indCol] == 'O'){
                Rocks rollingRock(numRows, indCol, false);
                rocks.push_back(rollingRock);
                mapRow.push_back(rockInd++);
            } else if (input[indCol] == '#'){
                Rocks fixedRock(numRows, indCol, true);
                rocks.push_back(fixedRock);
                mapRow.push_back(rockInd++);
            } else{
                mapRow.push_back(-1);
            }
        }
        rockMap.push_back(mapRow);
        numRows++;
    }


    ofstream outFile;
    outFile.open("weight.csv");
    for (long long i = 0; i < 40000; i++){
        spinCycle(rockMap, rocks);
        //if (i %1000000 ==0){
        //    cout << i/1000000 << "% " <<endl;
        //}

        int sumWeight = 0;
        for (auto & rock : rocks){
            if ( !rock.isFixed){
                sumWeight += numRows - rock.row;
            }
        }
        outFile << i << "," << sumWeight << endl;

    }

    



    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
 
    cout << "Runtime = " << duration.count() << endl;

}



void spinCycle(vector<vector<int>>& rockMap, vector<Rocks>& rocks){

        // tilt north 
        vector<int> lastFixedNorth;

        for(int indRow = 0; indRow < rockMap.size(); indRow++){
            for (int indCol = 0; indCol < rockMap[indRow].size(); indCol++){
                if (indRow == 0){
                    lastFixedNorth.push_back(0);
                }

                if (rockMap[indRow][indCol] ==-1){
                    continue;
                }

                int rockInd = rockMap[indRow][indCol];
                if (rocks[rockInd].isFixed) {
                    lastFixedNorth[indCol] = indRow+1;
                } else{
                    int newRow = lastFixedNorth[indCol]++;
                    if (newRow != rocks[rockInd].row){
                        rocks[rockInd].row = newRow;
                        rockMap[rocks[rockInd].row][indCol] = rockInd;
                        rockMap[indRow][indCol] = -1;
                    }
                }
            }
        }

        // tilt west (left)
        vector<int> lastFixedWest;

        for(int indCol = 0; indCol < rockMap[0].size(); indCol++){
            for (int indRow = 0; indRow < rockMap.size(); indRow++){
                if (indCol == 0){
                    lastFixedWest.push_back(0);
                }

                if (rockMap[indRow][indCol] ==-1){
                    continue;
                }

                int rockInd = rockMap[indRow][indCol];
                if (rocks[rockInd].isFixed) {
                    lastFixedWest[indRow] = indCol+1;
                } else{
                    int newCol = lastFixedWest[indRow]++;
                    if (newCol != rocks[rockInd].col){
                        rocks[rockInd].col = newCol;
                        rockMap[indRow][rocks[rockInd].col] = rockInd;
                        rockMap[indRow][indCol] = -1;
                    }
                }
            }
        }


        // tilt south (bottom) 

        vector<int> lastFixedSouth;

        for(int indRow = rockMap.size()-1; indRow >=0; indRow--){
            for (int indCol = 0; indCol < rockMap[indRow].size(); indCol++){
                if (indRow == rockMap.size()-1){
                    lastFixedSouth.push_back(rockMap.size()-1);
                }

                if (rockMap[indRow][indCol] ==-1){
                    continue;
                }

                int rockInd = rockMap[indRow][indCol];
                if (rocks[rockInd].isFixed) {
                    lastFixedSouth[indCol] = indRow-1;
                } else{
                    int newRow = lastFixedSouth[indCol]--;
                    if (newRow != rocks[rockInd].row){
                        rocks[rockInd].row = newRow;
                        rockMap[rocks[rockInd].row][indCol] = rockInd;
                        rockMap[indRow][indCol] = -1;
                    }
                }
            }
        }


        // tilt east (right)

        // tilt west (left)
        vector<int> lastFixedEast;

        for(int indCol = rockMap[0].size()-1; indCol >=0; indCol--){
            for (int indRow = 0; indRow < rockMap.size(); indRow++){
                if (indCol == rockMap[0].size()-1){
                    lastFixedEast.push_back(rockMap[0].size()-1);
                }

                if (rockMap[indRow][indCol] ==-1){
                    continue;
                }

                int rockInd = rockMap[indRow][indCol];
                if (rocks[rockInd].isFixed) {
                    lastFixedEast[indRow] = indCol-1;
                } else{
                    int newCol = lastFixedEast[indRow]--;
                    if (newCol != rocks[rockInd].col){
                        rocks[rockInd].col = newCol;
                        rockMap[indRow][rocks[rockInd].col] = rockInd;
                        rockMap[indRow][indCol] = -1;
                    }
                }
            }
        }

}
