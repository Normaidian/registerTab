#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "register.h"

using namespace std;

void Register::searching(string line, Group g, int width,string baseAddress, bool insideIf){
    Register r;

    if(line.find("line.")!=string::npos){
        line = line.substr(line.find("line."),line.size());
        r.name = line.substr(line.find('"')+1,line.find(',')-line.find('"')-1);                                                     //! Line name
        r.access = g.access;                                                                                                        //! Line access
        r.offset = "0x" + decToHex(hexToDec(line.substr(line.find("0x"),line.find('"')-1-line.find("0x")))+hexToDec(g.offset));     //! Line offset
        r.address =  "0x" + decToHex(hexToDec(r.offset) + hexToDec(baseAddress));                                                   //! Line address
        r.range = line.substr(line.find(".")+1,line.find(" ")-line.find("."));                                                      //! Line range

        if (insideIf == true){
            r.name = r.name + "**";
        }

        print(width,r);
    }else if(line.find("hide.")!=string::npos){
        line = line.substr(line.find("hide."),line.size());
        r.name = line.substr(line.find('"')+1,line.find(',')-line.find('"')-1);                                                     //! Line name
        r.access = g.access;                                                                                                        //! Line access
        r.offset = "0x" + decToHex(hexToDec(line.substr(line.find("0x"),line.find('"')-1-line.find("0x")))+hexToDec(g.offset));     //! Line offset
        r.address = "0x" + decToHex( hexToDec(r.offset) + hexToDec(baseAddress));                                                   //! Line address
        r.range = line.substr(line.find(".")+1,line.find(" ")-line.find("."));                                                      //! Line range

        if (insideIf == true){
            r.name = r.name + "**";
        }

        print(width,r);
    }
}

void Register::print(int width, Register r){
    string str, floor;

    //! Created string with blank space and floor equal in length of name column
    if (width > 23){
        for(int i = 0;i < width+6 ; i++){
            str = str + " ";
            floor = floor + "_";
        }
    }else{
        for(int i = 0;i < 23 ; i++){
            str = str + " ";
            floor = floor + "_";
        }
    }

    //! Printed table header
    if(first_print == true){
        cout << " " << floor << "________________________________________________________________________________" << endl;
        cout << "|" << str.substr(0,5) <<"Register name" << str.substr(0,str.length()-18) << "|";
        cout << str.substr(0,9) << "Access" << str.substr(0,9) << "|";
        cout << str.substr(0,7) << "Address" << str.substr(0,7) << "|";
        cout << str.substr(0,5) << "Offset" << str.substr(0,5) << "|";
        cout << str.substr(0,5) << "Range" << str.substr(0,5) << "|" << endl;
        cout << "|" << floor << "|________________________|_____________________|________________|_______________|" << endl;

        first_print = false;
    }

    cout << "|" << str.substr(0,3) << r.name << str.substr(0,str.length()-r.name.length()-3) << "|";                        //! print Register name
    cout << str.substr(0,5) << r.access << str.substr(0,24-r.access.length()-5) << "|";                                     //! print Register access
    cout << str.substr(0,5) << r.address << str.substr(0,21-r.address.length()-5) << "|";                                   //! print Register address
    cout << str.substr(0,6) << r.offset << str.substr(0,16-r.offset.length()-6) << "|";                                     //! print Register offset
    cout << str.substr(0,6) << r.range << str.substr(0,15-r.range.length()-6) << "|" << endl;                               //! print Register range
    cout << "|" << floor << "|________________________|_____________________|________________|_______________|" << endl;
}
