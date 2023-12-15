#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <map>
#include <limits.h>
#include <algorithm>

using namespace std;
class Node;

map<string, Node*> nodes;

void getNode(const string nodeName, Node& node);

// Recursive function to return gcd of a and b  
long long gcd(long long int a, long long int b) 
{ 
  if (b == 0) 
    return a; 
  return gcd(b, a % b); 
} 
  
// Function to return LCM of two numbers  
long long lcm(vector<int> arr) 
{ 
    long long ans = arr[0];
    for (int i = 1; i< arr.size(); i++ ){
                ans = (((arr[i] * ans)) /
                (gcd(arr[i], ans)));

    }
    return ans;
} 

class Node{
    public:
        Node* left;
        Node* right;
        string name;

        Node(const string node)
        {
            name = node;
        }

        void setLeft(Node* node){
            left = node;
        }

        string toString(){
            string value;
            value = "Name: " + name + " Left: "  + left->name + " Right: " + right->name;
            return value;
        }
};


int main(){

    string file = "inputDay8.txt";
    ifstream inputFile;
    inputFile.open(file);
    string input, directions;

    if (!getline(inputFile, directions)){
        cout << "Error Reading Directions" << endl;
    } 
    cout <<directions << endl;

    getline(inputFile, input); // read empty line
    
    Node start("AAA");
    nodes["AAA"] =  &start;
    Node* curNode = NULL;
    Node* leftNode = NULL;
    Node* rightNode = NULL;
    vector<Node*> startingNodes;

    while( getline(inputFile, input)){
        //cout << input << endl;
        //string curNodeStr = input.substr(0,3);
        //string leftNodeStr = input.substr(7,3);
        //string rightNodeStr = input.substr(12,3);
//
        //curNode = new Node(curNodeStr);
        //leftNode = new Node(leftNodeStr);
        //rightNode = new Node(rightNodeStr);
//
        //if (nodes.find(curNodeStr) != nodes.end()){
        //    curNode =  nodes[curNodeStr]; 
        //} else {
        //    nodes[curNodeStr] = curNode;
        //}
        //if (nodes.find(leftNodeStr) != nodes.end()){
        //    leftNode =  nodes[leftNodeStr]; 
        //} else {
        //    nodes[leftNodeStr] = leftNode;
        //}
//
        //if (nodes.find(rightNodeStr) != nodes.end()){
        //    rightNode =  nodes[rightNodeStr]; 
        //} else {
        //    nodes[rightNodeStr] = rightNode;
        //}
        getNode(input.substr(0,3), *curNode);
        getNode(input.substr(7,3), *leftNode);
        getNode(input.substr(12,3), *rightNode);
        curNode->left = leftNode;
        curNode->right = rightNode;

        if (curNode->name[2] == 'A'){
            startingNodes.push_back(curNode);
        }
        cout << curNode->toString() << endl;
    }
    vector<int> numSteps;
    for (int i = 0; i < startingNodes.size(); i++){
        numSteps.push_back(0);
        bool foundEnd = false;
        int directionInd = 0;
        int steps = 0;
        cout << directions << endl;
        while(!foundEnd ){
            char next = directions[directionInd++];

                cout << "Node " << startingNodes[i]->name << " ind " << directionInd << endl;
                cout << "Next step " <<next << endl; 
                if (next == 'R'){
                    startingNodes[i] = startingNodes[i]->right;
                } else {
                    startingNodes[i] = startingNodes[i]->left;
                }
                if (startingNodes[i]->name[2] == 'Z'){
                    foundEnd = true;
                }
            
            if (directionInd >= directions.size()){
                directionInd = 0;
            }
            
            numSteps[i]++;
        }
    }
    for (int i = 0; i < numSteps.size(); i++){

        cout << numSteps[i] << " steps" << endl;
    }
    cout << lcm(numSteps);





}

void getNode(const string nodeName, Node& node){
    if (nodes.find(nodeName) != nodes.end()){
        cout << "Node in map" <<endl;
        node =  *nodes[nodeName]; 
        cout << "Node found" << endl;
    } else {
        cout << "Making new Node" <<endl;
        Node* newNode = new Node(nodeName);
        node = *newNode;
        nodes[nodeName] = newNode;
    }
}