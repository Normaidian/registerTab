#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <list>
#include "register.h"

// NEXT: funkcja obsługująca for'y (tworzenie odpowiedniej ilości rejestrów),
//                           parametry z pliku *.p (wstawiajacy parametr za %(*))

using namespace std;

fstream file;
int width;
string fileAddress, baseAddress;

void allRegisterTabel();
string decToHex(string decAdd);
int hexToDec(string hexAdd);

Register r;
Group g;

int main(){
    system("cls");
    int choice;

    cout << " ____________________________________"<< endl;
    cout << "|               MENU                 |" << endl;
    cout << "|____________________________________|" << endl;
    cout << "|    1 - Get table with registers    |" << endl;
    cout << "|____________________________________|" << endl;
    cout << "|    9 - Exit                        |" << endl;
    cout << "|____________________________________|" << endl;
    cout << "Select operation: ";
    cin >> choice;

    switch(choice){

        case 1:
            allRegisterTabel();
        break;
        case 9:
            exit(0);
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
    //! Variables declaration
    fstream file;
    string line;
    bool insideIf = false, repeat = false;

    do{
        cout << "File address: ";
        cin >> fileAddress;

        file.open(fileAddress.c_str(), ios::in);

        if(!file.good()){
            cout << "---Wrong base address!---" << endl;
        }
    }while(!file.good());



    cout << "Base address: ";
    cin >> baseAddress;

    //! Checking corrections of base address
    for (int i = 2; i < baseAddress.length()-2;i++){
        if(!isxdigit(baseAddress[i])){
            cout << "---Wrong base address!---" << endl;
            system("pause");
            system("cls");
            main();
        }
    }

    system("cls");

    while(getline(file, line)){
        if((line.find("group.")!=string::npos)&&(repeat==false)){                       //! if in line is "*group*"
                g = g.searching(line);
        }else if(line.find("width")!=string::npos){                                     //! if in line is "*width*"
            if(line.find("0x")!=string::npos){
                if(r.hexToDec(line.substr(line.find("0x")+2,line.size())) > width){
                    width = r.hexToDec(line.substr(line.find("0x")+2,line.size()));
                }
            }else{
                if(atoi(line.substr(line.find("width ")+6,line.find(".")-line.find("width ")-1).c_str()) > width){
                    width = atoi(line.substr(line.find("width ")+6,line.find(".")-line.find("width ")-1).c_str());
                }
            }

            bool *pointer = &r.first_print;
            *pointer = true;
        }else if((line.find("if")!=string::npos)||(insideIf == true)){                  //! id inf line is "*if*"
                insideIf = true;

                 if(line.find("endif")!=string::npos){
                    insideIf = false;
                    repeat = false;
                 }else if((line.find("else")!=string::npos)||(line.find("elif")!=string::npos)||(repeat == true)){
                     repeat = true;
                 }else{
                    r.searching(line,g, width, baseAddress, insideIf);
                 }
        }else{                                                                          //! in other lines searching "*line*" and "*hide*"
            r.searching(line,g, width, baseAddress, insideIf);
        }
    }

    cout << endl << "Comments:" << endl;
    cout << "    1. Registers with 2 stars (**) after name are inside if, sif or %if conditions." << endl;


    system("pause");
    main();
}
