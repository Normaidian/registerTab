#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>

using namespace std;


fstream file,file2;
string road, groupAddHex, lineAddHex, lineName;
string tabGroup[3] ={"hgroup.", "rgroup", "group."};
string tabLine[2] ={"hide.", "line."};
string lineAddTab[2];   //  TUTAJ TZEBA CHYBA ZASTOSOWA� WSKA�NIKI
string lineNameTab[2];  //  TUTAJ TZEBA CHYBA ZASTOSOWA� WSKA�NIKI

string searchGroup(string line);
string searchLine(string groupAddHex,string line);
string fullAdd(string groupOff, string lineOff);

int main(){
    string line;
    bool tbreak =false;

    file.open("E:/Users/Normaidian/Desktop/intc.ph", ios::in);

    // zrobić try/catch
    if(file.good()==false){
        cout<< "Zly plik!" <<endl;
        exit(0);
    }

    while(getline(file, line)){
        for(int i = 0; i<3;i++){ //! 0-"hgroup.", 1-"rgroup", 2-"group."
            //! Searching hgroup/rgroup/group
            size_t position = line.find(tabGroup[i]);

            if(position!=string::npos){

                //! Cleaning empty space at line beginning
                line = line.substr(position,line.length());
                searchGroup(line);
                tbreak = true;
            }
        }
        if(tbreak == true)  break;
    }
    file.close();

    //! Output results
    for (int i = 0; i <sizeof(lineAddTab)/sizeof(string);i++){
        cout << lineAddTab[i] << " - " << lineNameTab[i]<<endl;
    }

    return 0;
}

string searchGroup(string line){

    for (int i = 0; i <line.length();i++){
        if(line.substr(i,i+5)=="group"||line.substr(i,i+6)=="rgroup"||line.substr(i,i+6)=="hgroup"){
            groupAddHex = line.substr(line.find("0x"),line.find("++")-line.find("0x"));

            searchLine(groupAddHex,line);
        }
    }

    return "??";
}

string searchLine(string groupAddHex, string temp_line){
    string line;
    int counter = 0, breakCounter = 0;

    file2.open("E:/Users/Normaidian/Desktop/intc.ph", ios::in);

    // zrobić try/catch
    if(file2.good()==false){
        cout<< "Zly plik!" <<endl;
        exit(0);
    }

    while(getline(file2, line)){
        if(breakCounter > 1)    break;

        // Za dużo lini wykrywa. Bierze jedną z następnej grupy
        // należy dynamicznie tworzyć wielkość tablic lineNameTab[] oraz lineAddTab[].
        // Potrzebna funkcja zliczająca ilośc lini w pliku i tworząca tablice odpowiedniej wielkości. Spróbować przy pomocy wskaźników.
        // Spróbować przerywać po wyszukaniu kolejnej grupy
        // Zrobić
        //! if (linia = group) && (wystapienie != 0)
        //!     break
        //! elif (linia = line)
        //!     linia do tabeli
        //! endif

        for(int i = 0; i<2;i++){ //! 0-"hide.", 1-"line"
            size_t position = line.find(tabLine[i]);

            if(position!=string::npos){
                //! Offset searching
                lineAddHex = line.substr(line.find("0x"),line.find('"')-line.find("0x")-1);
                lineAddTab[counter] = fullAdd(groupAddHex,lineAddHex);

                //! Line name searching
                lineNameTab[counter] = line.substr(line.find('"')+1,line.find(',')-line.find('"')-1);

                counter++;

                cout << "group: " << groupAddHex << " line: " << lineAddHex << " pelny: " << fullAdd(groupAddHex,lineAddHex) << " counter: " << counter << endl;

                if (lineAddHex == "0x00")   breakCounter++;
            }
        }
    }
    file2.close();
    return "??";
}

string fullAdd(string groupOff, string lineOff){
    int groupAddDec, lineAddDec;
    string fullAdd;
    std::stringstream ss, ss1, ss2;

    //! To Decimal
    ss << std::hex << groupOff;
    ss >> groupAddDec;
    ss1 << std::hex << lineOff;
    ss1 >> lineAddDec;

    //! Sum of decimal virables to Hexadecimal
    ss2 << std::hex << groupAddDec + lineAddDec;
    ss2 >> fullAdd;

    return fullAdd;
    return 0;
}
