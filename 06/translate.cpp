#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include "parser.h"
#include "translate.h"

using namespace std;

    string translate::translateJump(string jmp){
        
        if (jmp == "JGT"){
            return "001";
        }
        else if (jmp == "JEQ"){
            return "010";
        }
        else if (jmp == "JGE"){
            return "011";
        }
        else if (jmp == "JLT"){
            return "100";
        }
        else if (jmp == "JNE"){
            return "101";
        }
        else if (jmp == "JLE"){
            return "110";
        }
        else if (jmp == "JMP"){
            return "111";
        }
        else{
            return "000";
        }
    }
    string translate::translateComp(string cmp){
        if (cmp == "0")
        {
            return "101010";
        }
        else if(cmp == "1")
        {
            return "111111";
        }
        else if(cmp == "-1")
        {
            return "111010";
        }
        else if(cmp == "D")
        {
            return "001100";
        }
        else if(cmp == "A")
        {
            return "110000";
        }
        else if(cmp == "!D")
        {
            return "001101";
        }
        else if(cmp == "!A")
        {
            return "110001";
        }
        else if(cmp == "-D")
        {
            return "001111";
        }
        else if(cmp == "-A")
        {
            return "110011";
        }
        else if(cmp == "D+1")
        {
            return "011111";
        }
        else if(cmp == "A+1")
        {
            return "110111";
        }
        else if(cmp == "D-1")
        {
            return "001110";
        }
        else if(cmp == "A-1")
        {
            return "110010";
        }
        else if(cmp == "D+A")
        {
            return "000010";
        }
        else if(cmp == "D-A")
        {
            return "010011";
        }
        else if(cmp == "A-D")
        {
            return "000111";
        }
        else if(cmp == "D&A")
        {
            return "000000";
        }
        else if(cmp == "D|A")
        {
            return "010101";
        }
        else if(cmp == "M")
        {
            return "110000";
        }
        else if(cmp == "!M")
        {
            return "110001";
        }
        else if(cmp == "-M")
        {
            return "110011";
        }
        else if(cmp == "M+1")
        {
            return "110111";
        }
        else if(cmp == "M-1")
        {
            return "110010";
        }
        else if(cmp == "D+M")
        {
            return "000010";
        }
        else if(cmp == "D-M")
        {
            return "010011";
        }
        else if(cmp == "M-D")
        {
            return "000111";
        }
        else if(cmp == "D&M")
        {
            return "000000";
        }
        else if(cmp == "D|M")
        {
            return "010101";
        }
        else
        {
            return "";
        }
        
    }
    string translate::translateDest(string dst){
            if(dst == "M")
            {
                return "001";
            }
            else if(dst == "D")
            {
                return "010";
            }
            else if(dst == "MD")
            {
                return "011";
            }
            else if(dst == "A")
            {
                return "100";
            }
            else if(dst == "AM")
            {
                return "101";
            }
            else if(dst == "AD")
            {
                return "110";
            }
            else if(dst == "AMD")
            {
                return "111";
            }
            else
            {
                return "000";
            }
    }
    