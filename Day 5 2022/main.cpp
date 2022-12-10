#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <string>

using namespace std;

ifstream infile("data.txt");
long long int totalScore = 0;
long long int maximum = INT_MIN;

string crate1 = "LNWTD";
string crate2 = "CPH";
string crate3 = "WPHNDGMJ";
string crate4 = "CWSNTQL";
string crate5 = "PHCN";
string crate6 = "THNDMWQB";
string crate7 = "MBRJGSL";
string crate8 = "ZNWGVBRT";
string crate9 = "WGDNPL";

vector<string> crates = {crate1, crate2, crate3, crate4, crate5, crate6, crate7, crate8, crate9};

void processLine (string line, int day) {
    int amount, from, to;

    sscanf(line.c_str(), "move %d from %d to %d", &amount, &from, &to);
    string section = crates[from-1].substr(crates[from-1].length()-amount, amount);
    
    if(day == 1) reverse(section.begin(), section.end());

    crates[to-1] = crates[to-1] + section;
    crates[from-1] = crates[from-1].substr(0, crates[from-1].length()-amount);
}

void processNumbers (int day) {
    string line;
    infile.clear();
    infile.seekg(0);
    crates = {crate1, crate2, crate3, crate4, crate5, crate6, crate7, crate8, crate9};
    while (getline(infile, line)) {
        processLine(line, day);
    }
}

int main (void) {
    processNumbers(1);
    cout << "Day 1: ";
    for(int n = 0; n < crates.size(); n++) {
        cout << crates[n][crates[n].length()-1];
    }
    cout << endl;

    processNumbers(2);
    cout << "Day 2: ";
    for(int n = 0; n < crates.size(); n++) {
        cout << crates[n][crates[n].length()-1];
    }
    cout << endl;

    return 0;
}