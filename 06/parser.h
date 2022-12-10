#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

class parser{
    public:
    //parser();
    //bool isCommand(string);
    string cleanCommand(string);
    string setCommandType(string);
    string getComp(string);
    string getDest(string);
    string getJump(string);
    string getAddress(string);
    string binaryConvert(int);
    bool isLabel();
    private:
    string cBinary;
    int labelCount;
    bool label;
    vector<string> labels;
    string currentCommand;
    bool aCommand;
    bool cCommand;
    bool lCommand;
    string comp;
    string dest;
    string jump;
};

#endif