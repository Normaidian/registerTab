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

    int hexToDec(string hexAdd){
    int decAdd;
    std::stringstream ss;


    ss << std::hex << hexAdd;
    ss >> decAdd;

    return decAdd;
}

    string decToHex(int decAdd){
    string hexAdd;
    std::stringstream ss;


    ss << std::dec << decAdd;
    ss >> hexAdd;

    return hexAdd;
}
    void searching(string line, Group g, int width, bool insideIf);
    void print(int width,Register r);
};
