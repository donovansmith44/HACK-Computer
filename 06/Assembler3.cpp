#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include "parser.h"
#include "translate.h"

using namespace std;

bool is_number(string &s) {
  return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

int main(int argc, char* argv[]){
    string asmFile = argv[1];
    ifstream asmProg;
    ofstream hackFile;
    string line;
    vector<string> commands;    
    vector<string> commandType;
    vector<string> comp;
    vector<string> dest;
    vector<string> jump;
    vector<string> pointers;
    vector<string> binaryInstructions;
    vector<string> symbols;
    bool comment = false;
    parser parserObj;
    string cleanCommand;
    int varLoc = 16;
    
    //Symbol table module
    unordered_map<string, string> labels;
    ifstream readSymbols;
    string symbolMap = argv[2];
    readSymbols.open(symbolMap);
    
    while (getline(readSymbols, line)) //store all predefined symbols into unordered map
    {
        string symbol = "";
        string location = "";

        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == ' ')
            {
                for (int j = 0; j < i; j++) //store symbols
                {
                    symbol += line[j];
                }
                
                for (int k = i+1; k < line.length(); k++) //store symbol addresses
                {
                    location += line[k];
                }

                labels[symbol] = location; //store symbols and their addresses into unordered map
                
            }
        }
    }

    //Store all labels into the symbol table along with their associated addresses
    int instructionNum = 0;
    asmProg.open(asmFile);
    
    //*******FIRST PASS THROUGH FILE*******//
    while (getline(asmProg, line)) //read an assembly file
    {
        if (line[0] == '/' && line[1] == '/')
        {
            comment = true;
        }

        if (comment == false)
        {
            cleanCommand = parserObj.cleanCommand(line); //remove comments and whitespace
            
            if (!cleanCommand.empty()) //only add the command to the command vector if it's not an empty string
            {
                commands.push_back(cleanCommand);

                //if L_COMMAND, clean the label and place it into our hash table
                if (parserObj.setCommandType(cleanCommand) == "L_COMMAND")
                {
                    //remove the parentheses
                    cleanCommand.erase(0,1);
                    cleanCommand.erase(cleanCommand.length()-1, 1);
                    
                    labels[cleanCommand] = to_string(instructionNum);
                }          
                else
                {
                    instructionNum++;
                }
            }
        }
        
        comment = false;
    }

    //*******SECOND PASS THROUGH FILE*******//
    for (int i = 0; i < commands.size(); i++) //get the command attributes
    {
        string tempType = parserObj.setCommandType(commands[i]);
        string tempComp = "";
        string tempDest = "";
        string tempJump = "";
        string tempAddress = "";
        string tempBin = "";
        string newVar = "";
         
        commandType.push_back(tempType);

        //save the current commands attributes into corresponding vectors
        tempComp = parserObj.getComp(commands[i]);
        tempDest = parserObj.getDest(commands[i]);
        tempJump = parserObj.getJump(commands[i]);

        tempAddress = parserObj.getAddress(commands[i]);
        
        translate translator;

        if (commandType[i] == "A_COMMAND")
        {
            string tempSymbol = commands[i];
            
            tempSymbol.erase(0,1); //remove the @ sign

            if (!is_number(tempSymbol)) //symbol handling
            {
                if (labels.find(tempSymbol) != labels.end()) //if the symbol is in the symbol table
                {
                    if (is_number(labels[tempSymbol]))
                    {
                        tempBin = parserObj.binaryConvert(stoi(labels[tempSymbol])); //store the binary representation of the instructions
                    }
                }
                    else //Store a new variable into the symbol table with an address beginning at RAM 16
                    {
                        labels[tempSymbol] = to_string(varLoc);
                        tempBin = parserObj.binaryConvert(varLoc);
                        varLoc++;
                    }   
            }
            
            else //Address handling
            {
                tempBin = parserObj.binaryConvert(stoi(tempAddress));
            }
        }

        string a = "0"; //if a=1, M in comp. else, A in comp 

        string tempCommand = "noLabel";

        if (commandType[i] == "C_COMMAND")
        {
            tempBin = "111";
            
            for (int i = 0; i < tempComp.size(); i++)
            {
                if (tempComp[i] == 'M')
                {
                    a = "1";
                    break;
                }
                else
                {
                    a = "0";
                }     
            }

            tempBin += a;
            tempBin += translator.translateComp(tempComp);
            tempBin += translator.translateDest(tempDest);
            tempBin += translator.translateJump(tempJump);
        }

        comp.push_back(tempComp);
        dest.push_back(tempDest);
        jump.push_back(tempJump);
        pointers.push_back(tempAddress);
        binaryInstructions.push_back(tempBin);
        symbols.push_back(tempCommand);
    }

    readSymbols.close();
        
        //write binary code to hack file
        hackFile.open("binary.hack"); 
        for (int i = 0; i < binaryInstructions.size(); i++)
        {
            if (!binaryInstructions[i].empty())
            {
                hackFile << binaryInstructions[i] << endl;
            }   
        }
        
    hackFile.close();
    asmProg.close();

    return 0;
}