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
string road, groupAddHex, lineAddHex, lineName;
string tabGroup[3] ={"hgroup.", "rgroup", "group."};
string tabLine[2] ={"hide.", "line."};
string lineAddTab[44];   //  TUTAJ TZEBA CHYBA ZASTOSOWAC WSKAZNIKI
string lineNameTab[44];  //  TUTAJ TZEBA CHYBA ZASTOSOWAC WSKAZNIKI
int max_counter, counter = 1;

void searchGroup();
string searchLine(string groupAddHex,string line);
string fullAdd(string groupOff, string lineOff);

int main(){
    string line;
    bool tbreak =false;

    file.open("E:/Users/Normaidian/Desktop/intc.ph", ios::in);

    // zrobiæ try/catch
    if(file.good()==false){
        cout<< "Zly plik!" <<endl;
        exit(0);
    }


    while(getline(file, line)){     max_counter++;}

    file.close();

    while(counter<=max_counter){
        file.open("E:/Users/Normaidian/Desktop/intc.ph", ios::in);

        for(int skip=0;skip<=counter-1;skip++){
                getline(file,line);
        }

        for(int i = 0; i<3;i++){ //! 0-"hgroup.", 1-"rgroup", 2-"group."
            //! Searching hgroup/rgroup/group
            size_t position = line.find(tabGroup[i]);

            if(position!=string::npos){

                //! Cleaning empty space at line beginning
                line = line.substr(position,line.length());
                searchGroup();
            }
        }
        counter++;
        file.close();
    }

    //! Output results
    //!for (int i = 0; i <sizeof(lineAddTab)/sizeof(string);i++){
    //!    cout << lineAddTab[i] << " - " << lineNameTab[i]<<endl;
    //!}

    return 0;
}

void searchGroup(){

    string line;

    while((line.find("group")==string::npos)){
        getline(file,line);
        if(line.find("line.")!=string::npos){
            line = line.substr(line.find("line"),line.length());
            cout << line << endl;
        }else if(line.find("hide")!=string::npos){
            line = line.substr(line.find("hide"),line.length());
            cout << line <<endl;
        }
    }
}

string searchLine(string groupAddHex, string temp_line){


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
