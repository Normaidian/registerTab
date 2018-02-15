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
string tabGroup[3] = {"hgroup.", "rgroup", "group."};
string tabLine[2] = {"hide.", "line."};
string lineAddTab[44];   //  TUTAJ TZEBA CHYBA ZASTOSOWAC WSKAZNIKI
string lineNameTab[44];  //  TUTAJ TZEBA CHYBA ZASTOSOWAC WSKAZNIKI
int max_counter, counter = 1;

void searchRegister(string *fileTab,int current_line);
string fullAdd(string groupOff, string lineOff);

int main()
{
    string line, fileLocation = "";
    bool tbreak =false;

    //cin >> fileLocation;

    file.open("E:/Users/Normaidian/Desktop/intc.ph", ios::in);
    //file.open(fileLocation, ios::in);

    // zrobiæ try/catch
    if(file.good()==false)
    {
        cout<< "Zly plik!" <<endl;
        exit(0);
    }


    while(getline(file, line))
    {
        max_counter++;
    }

    file.close();

    string fileTab[max_counter];

    file.open("E:/Users/Normaidian/Desktop/intc.ph", ios::in);
    for(int i = 0; i < max_counter; i++)        getline(file,fileTab[i]);
    file.close();

    for(int j = 0; j<max_counter; j++)
    {

        if(fileTab[j].find("hgroup.")!=string::npos)
        {
            fileTab[j] = fileTab[j].substr(fileTab[j].find("hgroup"),fileTab[j].length());
            cout << fileTab[j] << endl;
            searchRegister(fileTab,j);

        }
        else if(fileTab[j].find("rgroup.")!=string::npos)
        {
            fileTab[j] = fileTab[j].substr(fileTab[j].find("rgroup"),fileTab[j].length());
            cout << fileTab[j] << endl;
            searchRegister(fileTab,j);
        }
        else if(fileTab[j].find("group.")!=string::npos)
        {
            fileTab[j] = fileTab[j].substr(fileTab[j].find("group"),fileTab[j].length());
            cout << fileTab[j] << endl;
            searchRegister(fileTab,j);
        }

    }

    //! Output results
    //!for (int i = 0; i <sizeof(lineAddTab)/sizeof(string);i++){
    //!    cout << lineAddTab[i] << " - " << lineNameTab[i]<<endl;
    //!}

    return 0;
}

void searchRegister(string *fileTab,int current_Line)
{

    string line;

    for( int i = current_Line+1; i < max_counter ; i++)
    {

        if(fileTab[i].find("line.")!=string::npos)
        {
            fileTab[i] = fileTab[i].substr(fileTab[i].find("line"),fileTab[i].length());
            cout << fileTab[i] << endl;
        }
        else if(fileTab[i].find("hide")!=string::npos)
        {
            fileTab[i] = fileTab[i].substr(fileTab[i].find("hide"),fileTab[i].length());
            cout << fileTab[i] <<endl;
        }
        else if(fileTab[i].find("group")!=string::npos)
        {
            break;
        }
    }
}

string fullAdd(string groupOff, string lineOff)
{
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
