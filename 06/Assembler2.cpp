#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include "parser.h"
#include "translate.h"

//this program takes two command line arguments: the name of an .asm file to parse, and the name of a text file containing symbols and addresses in a particular format.

//First pass, we store all of the symbol labels into our hash table along with the address of the command following the label.
//Second pass, we check if the symbol or variable is stored in our hash table already. If it is, then return the address associated with the symbol.
//If it's not, then add the new symbol as well as its corresponding address (16 onward for variables)
//The question is, how do we know what the address of a particular command acutally is?

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
    vector <vector <string> > instructions;
    int symbolAddress = 16;

    instructions.push_back(jump);
    instructions.push_back(dest);
    instructions.push_back(comp);
    instructions.push_back(commandType);
    instructions.push_back(commands);
    
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
    
    //*******FIRST PASS*******//
    while (getline(asmProg, line)) //read an assembly file
    {

        /*
        So we have the symbol table. Now what? Well, if we encounter a variable with the same name as our symbol table,
        then the binary output will be the instruction associated with the symbol.
        */

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
            }
        }

        //if L_COMMAND, clean the label and place it into our hash table
        if (parserObj.setCommandType(cleanCommand) == "L_COMMAND")
        {
            //remove the parentheses
            cleanCommand.erase(0,1);
            cleanCommand.erase(cleanCommand.length()-1, 1);
            
            labels[cleanCommand] = to_string(instructionNum + 1);
        }
        
        else
        {
            instructionNum++;
        }
        
        comment = false;
    }

    /*
    The following applies to A-Instructions:
    1. If the symbol of an A-Instruction is not a number
        i. If the symbol is in the symbol table
            a. Output the binary representation of the instruction number associated with the table's matching symbol
        i. If the symbol is not in the symbol table
            a. Store a new variable into the symbol table with an address beginning at RAM address 16
    */
        
    //now we can process the commands as a vector, all in one place where they can conveniently be accessed
    
    //get the command attributes
    for (int i = 0; i < commands.size(); i++)
    {
        string tempType = parserObj.setCommandType(commands[i]);
        string tempComp = "";
        string tempDest = "";
        string tempJump = "";
        string tempAddress = "";
        string tempBin = "";

        commandType.push_back(tempType);

        //save the current commands attributes into corresponding vectors
        tempComp = parserObj.getComp(commands[i]);
        tempDest = parserObj.getDest(commands[i]);
        tempJump = parserObj.getJump(commands[i]);

        tempAddress = parserObj.getAddress(commands[i]);

        if (is_number(tempAddress) && commandType[i] == "A_COMMAND") //if the address is a number (meaning necessarily that it is not a label), then convert the number to its binary form
        {
            tempBin = parserObj.binaryConvert(stoi(tempAddress));
        }
        
        string a = "0"; //if a=1, M in comp. else, A in comp 
        
        translate translator;
        
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
        
        else if(commandType[i] == "L_COMMAND") //get labels and add to symbol table
        {
            tempCommand = commands[i];
            if (tempCommand[0] == '(' || tempCommand[tempCommand.length()] == ')')
            {
                tempCommand.erase(tempCommand.length()-1, 1); //user defined labels will have ) as the last char. remove it
            }
            tempCommand.erase(0,1); //all labels (predefined and user-defined) have either ( or @ as the first char. Remove it

            //add labels to hash table if they're not there, get their address, convert it into a binary instruction and store into instructions vector
    
            //Add symbol to labeltable if it's not already there
            string testKey = tempCommand;
            if (labels.find(testKey) == labels.end())
            {
                labels[testKey] = to_string(symbolAddress);
                symbolAddress++;
            }

            tempBin = parserObj.binaryConvert(stoi(labels[testKey]));

        }

        comp.push_back(tempComp);
        dest.push_back(tempDest);
        jump.push_back(tempJump);
        pointers.push_back(tempAddress);
        binaryInstructions.push_back(tempBin);
        symbols.push_back(tempCommand);
    }

    readSymbols.close();

    for (int i = 0; i < commands.size(); i++)
    {
        cout << "COMMAND: " << commands[i] << endl; //i xx a cccccc ddd jjj
        cout << "comType: " << commandType[i] << endl; //16th bit
        cout << "comp   : " << comp[i] << endl; //6-11th bits
        cout << "dest   : " << dest[i] << endl; //3-5th bits
        cout << "jump   : " << jump[i] << endl; //0-2nd bits
        cout << "label: " << symbols[i] << endl; //addresses and labels
        cout << "binary : " << binaryInstructions[i] << endl;        
        cout << endl;
    }

        hackFile.open("binary.hack"); //write binary code to hack file
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