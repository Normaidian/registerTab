#include <iostream>
#include "group.h"

using namespace std;

class Register{
public:

    string offset;
    string name;
    string address;
    string range;
    string access;

    Register searching(string line, Group g, int width);
    void print(int width,Register r);
};
