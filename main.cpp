#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <windows.h>
#include <list>
#include <regex>
#include "register.h"

using namespace std;

fstream file;
int width, numberOfParams = 0;
string fileAddress, baseAddress, tempForLine, tempGroupLine;
bool first_print;

void allRegisterTabel();
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
Register r;
Group g;

int main(){
    system("cls");
    SetConsoleTextAttribute( hOut, 7);
    width = 0;

    do{
        int choice;

        cout << " ____________________________________"<< endl;
        cout << "|               MENU                 |" << endl;
        cout << "|____________________________________|" << endl;
        cout << "|    1 - Get table with registers    |" << endl;
        cout << "|____________________________________|" << endl;
        cout << "|    0 - Exit                        |" << endl;
        cout << "|____________________________________|" << endl;
        cout << "Select operation: ";
        cin >> choice;

        switch(choice){
            case 1:
                try{
                    allRegisterTabel();
                }catch(std::logic_error &e){
                    SetConsoleTextAttribute( hOut, 12 );
                    cout << e.what() << endl;
                    SetConsoleTextAttribute( hOut, 7 );
                    system("pause");
                    system("cls");
                }
            break;
            case 0:
                exit(0);
            break;
            default:
                SetConsoleTextAttribute( hOut, 12 );
                cout << "--Wrong choice---" << endl;
                SetConsoleTextAttribute( hOut, 7 );
                system("pause");
                system("cls");
            break;
        }



    }while(true);

    return 0;
}

void allRegisterTabel(){
    //! Variables declaration
    fstream file;
    string line;
    bool insideIf = false, insideIfElse = false, insideFor = false;

    do{                                                                                                                 //! Checking corrections of file address
        SetConsoleTextAttribute( hOut, 10 );
        cout << endl << "File address: ";
        SetConsoleTextAttribute( hOut, 7);
        cin >> fileAddress;

        file.open(fileAddress.c_str(), ios::in);

        if(!file.good()){
            throw(std::logic_error("---Wrong file address!---"));
        }
    }while(!file.good());



    SetConsoleTextAttribute( hOut, 10 );
    cout << "Base address: ";
    SetConsoleTextAttribute( hOut, 7 );
    cin >> baseAddress;

    for (int i = 2; i < baseAddress.length()-2;i++){                                                                    //! Checking corrections of base address
        if(!isxdigit(baseAddress[i])){
            throw(std::logic_error("---Wrong base address!---"));
        }
    }

    SetConsoleTextAttribute( hOut, 10 );                                                                                //! Creating tab with values from *.p file
    cout << "Number of values from file *.p: ";
    SetConsoleTextAttribute( hOut, 7 );
    cin >> numberOfParams;

    string tabParams[numberOfParams];

    for (int i =0; i < numberOfParams; i++){
        string value;
        SetConsoleTextAttribute( hOut, 10 );        cout << "Value of " << i+1 << " param: ";
        SetConsoleTextAttribute( hOut, 7 );
        cin >> value;

        tabParams[i] = value;
    }

    system("cls");

    while(getline(file, line)){

        for (int i = 1; i <= numberOfParams; i++){                                                                      //! Replace the parameter number with its value
            string param = "%(" + r.toString(i) + ")";

            while(line.find(param) != string::npos){
                line = line.replace(line.find(param),4,tabParams[i-1]);
            }
        }

        if((line.find("group.") != string::npos)){                                                                      //! creating Group object
                tempGroupLine = line;
                g = g.searching(line);
        }else if(line.find("width ") != string::npos){                                                                  //! setting values of width
            if(line.find("0x") != string::npos){
                if(r.hexToDec(line.substr(line.find("0x")+2,line.size())) > width){
                    width = r.hexToDec(line.substr(line.find("0x")+2,line.size()));
                }
            }else{
                if(atoi(line.substr(line.find("width ")+6,line.find(".")-line.find("width ")-1).c_str()) > width){
                    width = atoi(line.substr(line.find("width ")+6,line.find(".")-line.find("width ")-1).c_str());
                }
            }

            width = width+3;
            first_print = true;
        }else if(line.find("base ") != string::npos){
            baseAddress = line.substr(line.find("base ") + 5, line.size() - line.find("base ") + 5);
        }else if((line.find("%for") != string::npos)){                                                                  //! entry to for condition
            tempForLine = line;
            insideFor = true;
        }else if((line.find("%endfor") != string::npos)){                                                               //! exit from for condition
            insideFor = false;
        }else if(line.find("endif")!= string::npos){                                                                    //! exit to IF condition
            insideIf = false;
            insideIfElse = false;
        }else if((line.find("else") != string::npos)||(line.find("elif")!=string::npos)){                               //! entry to ELSE/ELIF condition
            insideIfElse = true;
        }else if((line.find("if ") != string::npos)){                                                                   //! entry to IF condition
            insideIf = true;
        }else if(((line.find("line.") != string::npos)||(line.find("hide.")!=string::npos))&&insideIfElse == false){    //! making register object and print it on screen
            if(insideFor == true){
                r.forOperations(line, tempForLine, tempGroupLine, width, baseAddress, insideIf, insideFor, first_print);
            }else{
                r = r.searching(line, g, baseAddress, insideIf, insideFor);
                r.print(width, r, first_print);
            }
            first_print = false;
        }
    }

    SetConsoleTextAttribute( hOut, 14 );
    cout << endl << "Comments:" << endl;
    cout << "    1. Registers with 1 stars (*) after name are inside for loop." << endl;
    cout << "    2. Registers with 2 stars (**) after name are inside if, sif or %if conditions." << endl;
    cout << "    3. Registers with 3 stars (***) after name are inside for loop and if, sif or %if conditions." << endl << endl;
    SetConsoleTextAttribute( hOut, 7 );

    file.close();
    system("pause");
    main();
}
