#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <list>
#include "register.h"

// NEXT: funkcja obsługująca for'y (tworzenie odpowiedniej ilości rejestrów),
//                           ify   (wypisująca dany rejestr tylko raz)
//                           parametry z pliku *.p (wstawiajacy parametr za %(*))

using namespace std;

fstream file;
int width;

void allRegisterTabel();
string decToHex(string decAdd);
int hexToDec(string hexAdd);

Register r;
Group g;

int main(){
    int choice;

    cout << " ____________________________________"<< endl;
    cout << "|               MENU                 |" << endl;
    cout << "|____________________________________|" << endl;
    cout << "|    1 - Get table with registers    |" << endl;
    cout << "|____________________________________|" << endl;
    cout << "Select operation: ";
    cin >> choice;

    switch(choice){

        case 1:
            system("cls");
            allRegisterTabel();
        break;
        default:
            cout << "---Wrong choice!---" << endl;
            system("pause");
            system("cls");
            main();
         break;
    }

    return 0;
}

void allRegisterTabel(){
    //! variables declaration
    fstream file;
    int actual_line = 0;
    string line;

    //! File open
    file.open("E:/Users/Normaidian/Desktop/intc.ph", ios::in);

    if(!file.good()){
        cout << "Wrong file!" << endl;
        exit(0);
    }

    int prevLine;

    while(getline(file, line)){
        actual_line++;
        if(line.find("group.")!=string::npos){              //! if in line is "*group*"
                g = g.searching(line);
        }else if(line.find("width")!=string::npos){         //! if in line is "*width*"
                if(line.find("0x")!=string::npos){
                    if(hexToDec(line.substr(line.find("0x")+2,line.size())) > width){
                        width = hexToDec(line.substr(line.find("0x")+2,line.size()));
                    }
                }else{
                    if(atoi(line.substr(line.find("width ")+6,line.find(".")-line.find("width ")-1).c_str()) > width){
                        width = atoi(line.substr(line.find("width ")+6,line.find(".")-line.find("width ")-1).c_str());
                    }
                }
        }else{                                              //! in other lines searching "*line*" and "*hide*"
            r.searching(line,g, width);
        }
    }
}

int hexToDec(string hexAdd){
    int decAdd;
    std::stringstream ss;


    ss << std::hex << hexAdd;
    ss >> decAdd;

    return decAdd;
}

string decToHex(string decAdd){
    string hexAdd;
    std::stringstream ss;


    ss << std::dec << decAdd;
    ss >> hexAdd;

    return hexAdd;
}
