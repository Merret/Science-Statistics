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
    cout << "Type the data file's path: ";
    cin.ignore();
    getline(cin, filePath);
    cout << endl;

    if(filePath.at(0)!='/') {
        filePath = "/"+filePath;
    }
    if(filePath.find('\ ')!=filePath.size()-1) {
        filePath.replace(filePath.find("\ ")-1, 1, "");
    }
    if(filePath.at(filePath.size()-1)==' ') {
        filePath.replace(filePath.size()-1, 1, "");
    }

    readFile();
    if(!isFileRead) {return 0;}
    calculate();
    answerTable();
    return 0;
}

void readFile() {
    inputFile.open(filePath);
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
        cs = "\033[1;31m";
        ce = "\033[0m";
    } else if(type=="information"||type=="i") {
        cs = "\033[1;34m";
        ce = "\033[0m";
    } else {
        cs = "";
        ce = "";
    }
    cout << cs << msg << ce << endl;
}

void answerTable() {
    cout << "========================================================================" << endl << "|  x  |  y  |  x̄  |  ȳ  | (x-x̄) | (y-ȳ) | (x-x̄)² | (y-ȳ)² | (x-x̄)(y-ȳ) |" << endl << "------------------------------------------------------------------------" << endl;
    for(long i = 0; i < x.size(); i++) {
        cout << setfill(' ') << setw(6) << x.at(i) << setfill(' ') << setw(6) << y.at(i) << setfill(' ') << setw(6) << xB << setfill(' ') << setw(6) << yB << setfill(' ') << setw(8) << x.at(i)-xB << setfill(' ') << setw(8) << y.at(i)-yB << setfill(' ') << setw(9) << (x.at(i)-xB)*(x.at(i)-xB) << setfill(' ') << setw(9) << (y.at(i)-yB)*(y.at(i)-yB) << setfill(' ') << setw(13) << (x.at(i)-xB)*(y.at(i)-yB) << endl;
    }
    cout << "========================================================================" << endl;
    cout << "\033[1;34mr=" << r << "  Regression line: Y = " << b << "X + " << a << "\033[0m" << endl;
}
