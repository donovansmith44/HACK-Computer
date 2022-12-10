#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

bool isNumber(string stringToCheck){
    bool isNum = true;

    for (int i = 0; i < stringToCheck.length(); i++)
    {
        if (!isdigit(stringToCheck[i]))
        {
            isNum = false;
            break;
        }
        
    }
    return isNum;
}

int main(){
    string s = "";

    while (s != "Q" && s!= "q")
    {
        cout << "Please enter a string." << endl;

        getline(cin, s);

        if (isNumber(s))
        {
        cout << "The string you've entered is a number!" << endl;
        }
        else if(s == "Q" || s == "q")
        {
            break;
        }
        else
        {
        cout << "The string is not a number." << endl;
        }
    }

    return 0;
}