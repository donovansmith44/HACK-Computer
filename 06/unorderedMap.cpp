#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

int main(){
    unordered_map<string, double> constants;

    string pi = "PI";
    string root2 = "ROOT2";
    string e = "E";

    //add some constants to the map
    constants[pi] = 3.141592653;
    constants[root2] = 1.414;

    //or

    constants.insert(make_pair(e, 2.718));

    //dump all values in map

    for (auto i = constants.begin(); i != constants.end(); i++)
    {
        cout << "Key: " << i->first << endl << "Value: " << i->second << endl;
    }
    
    // //how to check if value is in map
    // string lambda = "LAMBDA";

    // //end points to position after the last elements
    // if (constants.find(lambda) == constants.end())
    // {
    //     cout << "was not able to find: " << lambda << endl;
    // }
    // else
    // {
    //     cout << lambda << endl;
    // }
    return 0;
}