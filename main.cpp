#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>

// nalezy dynamicznie tworzyc wielkosc tablic lineNameTab[] oraz lineAddTab[].
// Potrzebna funkcja zliczajaca ilosc lini w pliku i tworzaca tablice odpowiedniej wielkosci. Sprobowaæ przy pomocy wskaznikow.
// dorobiæ pomijanie grup które ju¿ s¹ zczytane
// CZY OTWIEANIE I ZAMYKANIE PLIKU W PETLI JEST OK?

using namespace std;


fstream file;
string road, groupAddHex, lineAddHex, lineName, baseAddres;
string tabGroup[3] = {"hgroup.", "rgroup", "group."};
string tabLine[2] = {"hide.", "line."};
string lineAddTab[44];   //  TUTAJ TZEBA CHYBA ZASTOSOWAC WSKAZNIKI
string lineNameTab[44];  //  TUTAJ TZEBA CHYBA ZASTOSOWAC WSKAZNIKI
int max_counter, counter = 1;

void searchRegister(string *fileTab,int current_line,string baseOffset);
string fullAdd(string groupOff, string lineOff);

int main(){
    cout << "Base address: ";
    cin >> baseAddres;

    string line, fileLocation = "";
    bool tbreak =false;

    //cin >> fileLocation;

    file.open("E:/Users/Normaidian/Desktop/intc.ph", ios::in);
    //file.open(fileLocation, ios::in);

    // zrobiæ try/catch
    if(file.good()==false){
        cout<< "Zly plik!" <<endl;
        exit(0);
    }


    while(getline(file, line)){
        max_counter++;
    }

    file.close();

    string fileTab[max_counter];

    file.open("E:/Users/Normaidian/Desktop/intc.ph", ios::in);
    for(int i = 0; i < max_counter; i++)        getline(file,fileTab[i]);
    file.close();

    for(int j = 0; j<max_counter; j++){

        if(fileTab[j].find("hgroup.")!=string::npos)
{
            fileTab[j] = fileTab[j].substr(fileTab[j].find("hgroup"),fileTab[j].length());
            groupAddHex = fileTab[j].substr(fileTab[j].find("0x"),fileTab[j].find("++")-fileTab[j].find("0x"));
            searchRegister(fileTab,j,groupAddHex);
        }
        else if(fileTab[j].find("rgroup.")!=string::npos){
            fileTab[j] = fileTab[j].substr(fileTab[j].find("rgroup"),fileTab[j].length());
            groupAddHex = fileTab[j].substr(fileTab[j].find("0x"),fileTab[j].find("++")-fileTab[j].find("0x"));
            searchRegister(fileTab,j,groupAddHex);
        }
        else if(fileTab[j].find("group.")!=string::npos){
            fileTab[j] = fileTab[j].substr(fileTab[j].find("group"),fileTab[j].length());
            groupAddHex = fileTab[j].substr(fileTab[j].find("0x"),fileTab[j].find("++")-fileTab[j].find("0x"));
            searchRegister(fileTab,j,groupAddHex);
        }
    }

    //! Output results
    //!for (int i = 0; i <sizeof(lineAddTab)/sizeof(string);i++){
    //!    cout << lineAddTab[i] << " - " << lineNameTab[i]<<endl;
    //!}

    return 0;
}

void searchRegister(string *fileTab,int current_Line, string baseOffset){

    cout << " ______________________________________" << endl;
    cout << "|   Register Name    |   Full Address  |" << endl;
    cout << "|____________________|_________________|" << endl;


    for( int i = current_Line+1; i < max_counter ; i++){

        if(fileTab[i].find("line.")!=string::npos){
            string registerName = fileTab[i].substr(fileTab[i].find('"')+1,fileTab[i].find(",")-fileTab[i].find('"')-1);
            string registerFullOffset = fullAdd(baseOffset,fileTab[i].substr(fileTab[i].find("0x"),fileTab[i].find("++")-fileTab[i].find("0x")));

            int numOfSpace1 = (20 - registerName.length()), numOfSpace2 = (17 - registerFullOffset.length());
            string space = "                                         ";

            cout << "|" << space.substr(0,6) << registerName << space.substr(0,numOfSpace1-6) << "|";
            cout << space.substr(0,3) << "0x" << registerFullOffset << space.substr(0,numOfSpace2-5) << "|" << endl;
        }
        else if(fileTab[i].find("hide")!=string::npos){
            string registerName = fileTab[i].substr(fileTab[i].find('"')+1,fileTab[i].find(",")-fileTab[i].find('"')-1);
            string registerFullOffset = fullAdd(baseOffset,fileTab[i].substr(fileTab[i].find("0x"),fileTab[i].find("++")-fileTab[i].find("0x")));

            int numOfSpace1 = (20 - registerName.length()), numOfSpace2 = (17 - registerFullOffset.length());
            string space = "                                         ";

            cout << "|" << space.substr(0,6) << registerName << space.substr(0,numOfSpace1-6) << "|";
            cout << space.substr(0,3) << "0x" << registerFullOffset << space.substr(0,numOfSpace2-5) << "|" << endl;
        }
        else if(fileTab[i].find("group")!=string::npos){
            break;
        }
    }
    cout << "|____________________|_________________|" << endl;
}

string fullAdd(string groupOff, string lineOff){
    int baseAddDec, groupAddDec, lineAddDec;
    string fullAdd;
    std::stringstream ss, ss1, ss2, ss3;

    //! To Decimal
    ss << std::hex << baseAddres;
    ss >> baseAddDec;
    ss1 << std::hex << groupOff;
    ss1 >> groupAddDec;
    ss2 << std::hex << lineOff;
    ss2 >> lineAddDec;

    //! Sum of decimal virables to Hexadecimal
    ss3 << std::hex << baseAddDec + groupAddDec + lineAddDec;
    ss3 >> fullAdd;

    return fullAdd;
    return 0;
}
