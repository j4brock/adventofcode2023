#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits.h>
#include <algorithm>
#include <map>
#include <memory>

using namespace std;

const string file = "inputDay15.txt";


class Lens{
    public:
        string label;
        int lensWidth;
        Lens(string label, int lensWidth){
            this->label = label;
            this->lensWidth = lensWidth;
        }
        

};

class LensBox{
    public:

        int id;

        vector<Lens*> lenses;

        LensBox(int id){
            this->id = id;
        }

        void remove(string label){
            int ind = 0;
            bool isFound = false;
            while ( !isFound && ind < lenses.size()){
                if (lenses[ind]->label == label){
                    isFound = true;
                    lenses.erase(lenses.begin()+ind);
                }

                ind++;
            } 
        }

        void add(string label, int lensSize){
            int ind = 0;
            bool isFound = false;

            while ( !isFound && ind < lenses.size()){
                if (lenses[ind]->label == label){
                    isFound = true;
                    lenses[ind]->lensWidth = lensSize;
                }

                ind++;
            } 

            if (!isFound){
                Lens* lens = new Lens(label, lensSize);
                lenses.push_back(lens);
            }

        }

        int getPower(){
            int slotNum = 1, sum = 0;
            for (auto & lense : lenses){
                sum+= (id+1) * slotNum++ * lense->lensWidth;
            }
            return sum;
        }



};


int main(){

    ifstream inputFile;
    inputFile.open(file);
    string input;
    int sum = 0;

    map<int, LensBox*> boxes;

    while(getline(inputFile, input, ',')){

        int val = 0;

        int ind = 0;
        char op = '.';
        LensBox* curBox;
        string label = "";
        for(char &c : input){
            if ( c =='-' || c == '='){
                op = c;
                if (boxes.find(val) == boxes.end()){
                    curBox = new LensBox(val);
                    boxes[val] = curBox;
                } else {
                    curBox = boxes[val];
                } 

                if (op == '-'){
                    boxes[val]->remove(label);
                }


            } else if (op != '.'){
                int lensWidth = int(c) -48;
                curBox->add(label, lensWidth);
            } else {
                val += int(c);
                val *= 17;
                val %= 256;
                label += c;
            }
        }

        sum += val;

    }
    cout << "Sum is " << sum << endl;
    int lenseSum = 0;
    for (auto & box : boxes){
        lenseSum += box.second->getPower();
    }
        cout << "Lense Sum is " << lenseSum << endl;

}