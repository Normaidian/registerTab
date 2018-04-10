#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <list>
#include "register.h"

// nalezy dynamicznie tworzyc wielkosc tablic lineNameTab[] oraz lineAddTab[].
// NEXT: funkcja obsługująca for'y (tworzenie odpowiedniej ilości rejestrów)
// IN PROGRESS: funkcja drukująca wiersze

using namespace std;


fstream file;
string road;
int width;
int max_counter;
bool insideGroup = false;

void allRegisterTabel();
void searchRegister(string *fileTab,int current_line,string baseOffset);
void printRow(string registerAddress, string registerName, string registerOffset, string registerSize);
string fullAdd(string groupOff, string lineOff);
string decToHex(string decAdd);
int hexToDec(string hexAdd);

string file_location = "E:/Users/Normaidian/Desktop/intc.ph";
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

    //! Finding group
    while(getline(file, line)){
        actual_line++;
        if(line.find("group.")!=string::npos){
                g = g.searching(line);
        }else if(line.find("width")!=string::npos){
                if(line.find("0x")!=string::npos){
                    width = hexToDec(line.substr(line.find("0x")+2,line.size()));
                }else{
                    width = atoi(line.substr(line.find("width ")+6,line.find(".")-line.find("width ")-1).c_str());
                }
        }else{
            r.searching(line,g, width);
        }
    }
}




void searchRegister(string *fileTab,int current_Line, string baseOffset){
    for( int i = current_Line+1; i < max_counter ; i++){

        if((fileTab[i].find("line.")!=string::npos)||(fileTab[i].find("hide")!=string::npos)){


            //printRow(registerAddress,registerName,registerOffset,registerRange);
        }
        else if(fileTab[i].find("group")!=string::npos){
            break;
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
