#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <math.h>
#include <string>
using namespace std;

ifstream inputFile;
vector<float> x, y;
float xB, yB, r, a, b;
int isFileRead=0;
string filePath;
void readFile();
void Msg(string msg, string type);
void calculate();
void answerTable();

int main()
{
    string exit;
    cout << "Type the data file's path: ";
    getline(cin, filePath);
    cout << endl;
    readFile();
    if(!isFileRead) {return 0;}
    calculate();
    answerTable();
    cout << "Type 'exit' to close the application." << endl;
    while(cin>>exit) {
        if(exit=="exit")
            return 0;
    }
    return 0;
}

void readFile() {
    inputFile.open(filePath.c_str());
    if(inputFile.fail()) {
        Msg("Error: No data file.", "e");
        Msg("Please check the file path again.", "e");
        Msg("Wrong file path: " + filePath, "e");
        return;
    }
    isFileRead = 1;
    Msg("selected file path: " + filePath, "i");
    Msg("Data file accept.", "i");
    Msg("Reading file...", "i");
    float tmp;
    for(long i = 0; inputFile>>tmp; i++) {
        x.push_back(tmp);
        float tmp2;
        inputFile>>tmp2;
        y.push_back(tmp2);
    }
    Msg("File read.", "i");
}

void calculate() {
    Msg("Calculating data...", "i");
    float tmpSegXY=0, tmpSegX=0, tmpSegY=0;
    for(long i = 0; i < x.size(); i++) {
        xB += x.at(i);
        yB += y.at(i);
    }
    xB = xB/x.size();
    yB = yB/y.size();
    for(long i = 0; i < x.size(); i++) {
        tmpSegXY += (x.at(i)-xB)*(y.at(i)-yB);
        tmpSegX += (x.at(i)-xB)*(x.at(i)-xB);
        tmpSegY += (y.at(i)-yB)*(y.at(i)-yB);
    }
    r=tmpSegXY/(sqrt(tmpSegX)*sqrt(tmpSegY));
    b=tmpSegXY/tmpSegX;
    a=yB-b*xB;
    Msg("Data Calculation is done.", "i");
}

void Msg(string msg, string type) {
    string cs, ce;
    if(type=="error"||type=="e") {
        cs = "";
        ce = "";
    } else if(type=="information"||type=="i") {
        cs = "";
        ce = "";
    } else {
        cs = "";
        ce = "";
    }
    cout << cs << msg << ce << endl;
}

void answerTable() {
    cout << "==========================================================================================================" << endl << "|  x  |  y  |  xBar  |  yBar  | (x-xBar) | (y-yBar) | square(x-xBar) | square(y-yBar) | (x-xBar)(y-yBar) |" << endl << "----------------------------------------------------------------------------------------------------------" << endl;
    for(long i = 0; i < x.size(); i++) {
        cout << setfill(' ') << setw(6) << x.at(i) << setfill(' ') << setw(6) << y.at(i) << setfill(' ') << setw(9) << xB << setfill(' ') << setw(9) << yB << setfill(' ') << setw(11) << x.at(i)-xB << setfill(' ') << setw(11) << y.at(i)-yB << setfill(' ') << setw(17) << (x.at(i)-xB)*(x.at(i)-xB) << setfill(' ') << setw(17) << (y.at(i)-yB)*(y.at(i)-yB) << setfill(' ') << setw(19) << (x.at(i)-xB)*(y.at(i)-yB) << endl;
    }
    cout << "==========================================================================================================" << endl;
    cout << "r=" << r << "  Regression line: Y = " << b << "X + " << a << endl;
}
