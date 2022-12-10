#ifndef TRANSLATE_H
#define TRANSLATE_H
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include "parser.h"

using namespace std;

class translate{
    public:
    string translateJump(string);
    string translateComp(string);
    string translateDest(string); 
};


#endif