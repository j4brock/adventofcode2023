#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits.h>
#include <algorithm>
#include <memory>

using namespace std;

const string file = "inputDay10.txt";
class Node;
vector<shared_ptr<Node>> parseNodes(string line, int rowInd);
void linkNodes(vector<shared_ptr<Node>>& line1, vector<shared_ptr<Node>>& line2, vector<shared_ptr<Node>>& line3, bool isFirstLine, bool isLastLine, shared_ptr<Node>& startNode);
int traverseMap(shared_ptr<Node> start);
int findArea(vector<vector<shared_ptr<Node>>>& grid);

class Node{

    public: 
        char symbol;
        bool isStartNode = false;
        shared_ptr<Node> next1 = nullptr;
        shared_ptr<Node> next2 = nullptr;
        int rowInd;
        int colInd;
        bool isLoop = false;

        Node(char symb){
            this->symbol = symb;
        }

        shared_ptr<Node> getNext(shared_ptr<Node> prev){
            isLoop = true;
            if (prev == nullptr || prev == next2){
                return next1;
            } else {
                return next2;
            }
        }

        void addNext(shared_ptr<Node> next){
            if (next1 == nullptr){
                next1 = next;
            } else {
                next2 = next;
            }
        }

};


int main(){

    ifstream inputFile;
    inputFile.open(file);
    string input;
    int numCols, numRows;
    
    vector<vector<shared_ptr<Node>>> lines;
    int rowInd = 0;
    bool isFirstLine = true, isLastLine = false;
    if (getline(inputFile, input)){
        lines.push_back(parseNodes(input, rowInd));
    }
    rowInd++;
    shared_ptr<Node> startNode = nullptr;

    if (getline(inputFile, input)){
        lines.push_back(parseNodes(input, rowInd));
    }
    numCols = lines[rowInd].size();
    linkNodes(lines[rowInd-1], lines[rowInd-1], lines[rowInd], isFirstLine, isLastLine, startNode);
    rowInd++;
    isFirstLine = false;

    while( getline(inputFile, input)){

        lines.push_back(parseNodes(input, rowInd));
        linkNodes(lines[rowInd-2], lines[rowInd-1], lines[rowInd], isFirstLine, isLastLine, startNode);
        rowInd++;
    }

    isLastLine = true;
    linkNodes(lines[rowInd-2], lines[rowInd-1], lines[rowInd-1], isFirstLine, isLastLine, startNode);

    int steps = traverseMap(startNode);
    cout << "Farthest distance is " << steps /2 << endl;

    numRows = rowInd;

    int area = findArea(lines);
    cout << "Area between pipes is " << area << endl;

}

int findArea(vector<vector<shared_ptr<Node>>>& grid){
    vector<bool> betweenPipesCol;
    vector<char> lastPipeCol;
    int area = 0;
    for (int indRow = 0; indRow < grid.size(); indRow++){
        bool betweenPipesRow = false;
        char lastPipeRow = '.';
        for (int indCol = 0; indCol < grid[indRow].size(); indCol++){

            if (betweenPipesCol.size() < grid[indRow].size()){ // will be created through first iteration
                betweenPipesCol.push_back(false);
                lastPipeCol.push_back('.');
            }

            if (grid[indRow][indCol]->isLoop){
                char curSymbol = grid[indRow][indCol]->symbol;
                if ( curSymbol != '-'){
                    if (//(curSymbol == 'F' && lastPipeRow == 'J') ||
                        (curSymbol == 'J' && lastPipeRow == 'F') ||
                        (curSymbol == '7' && lastPipeRow == 'L') 
                        //(curSymbol == 'L' && lastPipeRow == '7')
                        ){
                        lastPipeRow = curSymbol;
                    } else {
                        betweenPipesRow = !betweenPipesRow;
                        lastPipeRow = curSymbol;
                    }
                }
                if (curSymbol != '|'){
                    if (//(curSymbol == 'F' && lastPipeCol[indCol] == 'J') ||
                        (curSymbol == 'J' && lastPipeCol[indCol] == 'F') ||
                        //(curSymbol == '7' && lastPipeCol[indCol] == 'L') ||
                        (curSymbol == 'L' && lastPipeCol[indCol] == '7')){
                        lastPipeCol[indCol] = curSymbol;
                    } else {
                        lastPipeCol[indCol] = curSymbol;
                        betweenPipesCol[indCol] = !betweenPipesCol[indCol];
                    }
                }
            } else if (betweenPipesRow && betweenPipesCol[indCol]){
                area++;
                cout << "Row " << indRow <<" Col " << indCol << endl; 
            }
        }

    }

    return area;
}


int traverseMap(shared_ptr<Node> start){
    shared_ptr<Node> prevNode = nullptr;
    shared_ptr<Node> curNode = start;
    shared_ptr<Node> nextNode = nullptr;
    int numSteps = 0;
    do{
        nextNode = curNode->getNext(prevNode);
        prevNode = curNode;
        curNode = nextNode;
        numSteps++;
        if (curNode == nullptr){
            cerr << "Error ran into edge of map with null pointer" << endl;
        }
    } while (!curNode->isStartNode);

    return numSteps;

}

void linkNodes(vector<shared_ptr<Node>>& line1, vector<shared_ptr<Node>>& line2, vector<shared_ptr<Node>>& line3, bool isFirstLine, bool isLastLine, shared_ptr<Node>& startNode){

    for (int indCol = 0; indCol < line2.size(); indCol++){

        switch(line2[indCol]->symbol){
            case '|':
                if (!isFirstLine){
                    line2[indCol]->next1 = line1[indCol];
                }
                if (!isLastLine){
                    line2[indCol]->next2 =line3[indCol];
                }
                break;
            case '-':
                if (indCol > 0){
                    line2[indCol]->next1 = line2[indCol-1];
                }
                if (indCol < line2.size()-1){
                    line2[indCol]->next2 = line2[indCol+1];
                }

                break;
            case 'F':
                if (indCol < line2.size()-1){
                    line2[indCol]->next1 = line2[indCol+1];
                }
                if (!isLastLine){
                    line2[indCol]->next2 = line3[indCol];
                }

                break;
            case 'J':
                if (!isFirstLine){
                    line2[indCol]->next1 = line1[indCol];
                }
                if (indCol > 0){
                    line2[indCol]->next2 = line2[indCol-1];
                }
                break;
            case 'L':
                if (!isFirstLine){
                    line2[indCol]->next1 = line1[indCol];
                }
                if (indCol < line2.size()-1){
                    line2[indCol]->next2 = line2[indCol+1];
                }

                break;
            case '7':
                if (indCol > 0){
                    line2[indCol]->next1 = line2[indCol-1];
                }
                if (!isLastLine){
                    line2[indCol]->next2 = line3[indCol];
                }
                break;
            case 'S':
            {
                bool above = false, below = false, left = false, right = false;
                startNode = line2[indCol];
                startNode->isStartNode = true;
                if (!isFirstLine && (line1[indCol]->symbol == '|' || line1[indCol]->symbol == '7' || line1[indCol]->symbol == 'F')){
                    startNode->addNext(line1[indCol]);
                    above = true;
                }
                if (indCol>0 && (line2[indCol-1]->symbol == '-' || line2[indCol-1]->symbol == 'L' || line2[indCol-1]->symbol == 'F')){
                    startNode->addNext(line2[indCol-1]);
                    left = true;
                }
                if (indCol<line2.size()-1 && (line2[indCol+1]->symbol == '-' || line2[indCol+1]->symbol == 'J' || line2[indCol+1]->symbol == '7')){
                    startNode->addNext(line2[indCol+1]);
                    right = true;
                }
                if (!isLastLine && (line3[indCol]->symbol == '|' || line3[indCol]->symbol == 'J' || line3[indCol]->symbol == 'L')){
                    startNode->addNext(line3[indCol]);
                    below = true;
                }
                if (above){
                    if (below){
                        startNode->symbol = '|';  
                    }
                    else if (left){
                        startNode->symbol = 'J';  

                    }
                    else if (right){
                        startNode->symbol = 'L';  

                    }
                } else if(below) {
                    if (left){
                        startNode->symbol = '7';  
                    } else if(right){
                        startNode->symbol = 'F';  
                    }
                } else {
                    startNode->symbol = '-';  
                }



                break;
            }
            default:
                break; // if . do nothing no linking
        }
        

    }

}


vector<shared_ptr<Node>> parseNodes(string line, int rowInd){

    vector<shared_ptr<Node>> nodes;
    for (int i = 0; i < line.size(); i++){
        nodes.push_back(make_shared<Node>(Node(line[i])));
        nodes[i]->rowInd = rowInd;
        nodes[i]->colInd = i;
    }
    return nodes;
}
