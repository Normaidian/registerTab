#include <iostream>
#include "group.h"

using namespace std;

class Register{
public:

    bool first_print = true;

    string offset;
    string name;
    string address;
    string range;
    string access;

    int hexToDec(string hexAdd){                                                            //! Convert hex number to decimal number
        int decAdd;
        std::stringstream ss;

        ss << std::hex << hexAdd;
        ss >> decAdd;

        return decAdd;
    }

    string decToHex(int decAdd){                                                            //! Convert decimal number to hex number
        string hexAdd;
        std::stringstream ss;

        ss << std::hex << decAdd;
        ss >> hexAdd;

        return hexAdd;
    }

    string toString(int numberI){
        string numberS;

        std::stringstream ss;

        ss << numberI;
        ss >> numberS;

        return numberS;
    }
    void searching(string line, Group g, int width, string baseAddress, bool insideIf, bool insideFor);     //! Searching registers in line from file
    void print(int width,Register r);                                                       //! Printed row in console
    void forOperations(string line, string tempForLine, string tempGroupLine, int width, string baseAddress, bool insideIf, bool insideFor);
};
