#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include "parser.h"

using namespace std;

string parser::setCommandType(string curCommand){
        /*
        1. If the string starts with @, it's an A-command
        2. If the string starts with (, it's an L-command
        3. All others are C-instructions
        */
      bool isNum = !curCommand.empty() && std::all_of(curCommand.begin()+1, curCommand.end(), ::isdigit);

       if (curCommand[0] == '@')
       {
        aCommand = true;
        return "A_COMMAND";
       }

       else if (curCommand[0] == '(')
       {
        lCommand = true;
        return "L_COMMAND";
       }

        else
        {
            cCommand = true;
        return "C_COMMAND";
        }
    }

string parser::cleanCommand(string command){
    
    string cleanedCommand;

    for (int i = 0; i < command.length(); i++) //remove comments from lines
        {
            if(command[i] == '/' && command[i+1] == '/'){
              command.erase(i, command.length()-i);
              break;
            }
        }

    for (int i = 0; i < command.length(); i++) //remove spaces from lines
    {
        if (!isspace(command[i]))
        {
            cleanedCommand += command[i];
        }
        
    }

    return cleanedCommand;

}

string parser::getComp(string command){
    comp = "";
    int pos = 0;
    bool isComp = false;
    bool hasDest = false;
    bool hasJump = false;

    //comp is everything to the right of the equal sign
    for (int i = 0; i < command.length(); i++)
    {
        if (command[i] == '=')
        {
            pos = i;
            hasDest = true;
            break;
        }

        if (command[i] == ';')
        {
            pos = i;
            hasJump = true;
            break;
        }
        
    }
    
    if (hasDest)
        {
            for (int i = pos+1; i < command.length(); i++)
            {
                comp += command[i];
            }
        }

    else if (hasJump)
        {
            for (int i = 0; i < pos; i++)
            {
                comp += command[i];
            }
        }

    return comp;
}

string parser::getDest(string command){
    dest = "";
    int pos = 0;
    bool isDest = false;

    //dest is everything to the left of the equal sign
        for (int i = 0; i < command.length(); i++)
        {
            if (command[i] == '=')
            {
                pos = i;
                isDest = true;
                break;
            }
        }
    
        for (int i = 0; i < pos; i++)
        {
            if (isDest)
            {
                dest += command[i];
            }
        }

        return dest;       
    }
 
 string parser::getJump(string command){
    jump = "";
    int pos = 0;
    bool hasJump = false;

    for (int i = 0; i < command.length(); i++)
    {
        if (command[i] == ';')
        {
            pos = i;
            hasJump = true;
            break;
        }
        
    }
    
    if (hasJump)
    {
        for (int i = pos+1; i < command.length(); i++)
        {
            jump += command[i];
        }
        
    }
    
    return jump;
 }

 string parser::binaryConvert(int decimalNum){
        string binary = "";

    for (int i = 16; i > 0; i--)
    {
        if (decimalNum >= pow(2,i-1))
        {
            binary +=  '1';
            decimalNum -= pow(2, i-1);
        }
        else{
            binary +=  '0';
        }
    }
        return binary;
 }

 string parser::getAddress(string address){
    string cleanAddress = "";
    label = false;
    labels.clear();

    for (int i = 1; i < address.length(); i++) //remove the @ symbol from A-commands
    {
        cleanAddress += address[i];
        
        if (int(address[i]) != '0' || int(address[i]) != '1' || int(address[i]) != '2' || int(address[i]) != '3' || int(address[i]) != '4' || int(address[i]) != '5' || int(address[i]) != '6' || int(address[i]) != '7' || int(address[i]) != '8' || int(address[i]) != '9')
        {
            label = true;
        }
        
    }

    if (label) //if any of the characters in the address name aren't integers, then we know that the A-Command contains a predefined label. store labels in a vector.
    {
        labels.push_back(cleanAddress);
    }
    else
    {
        labels.push_back("");
    }
    return cleanAddress;
    
 }

 bool parser::isLabel(){
    return label;
 }