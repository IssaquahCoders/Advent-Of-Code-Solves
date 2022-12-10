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
vector<int> list;
unordered_set<int> defaultSet;
bool checked = false;

string myStrings[3];
void processLine (string line, int day) {
    int f1, f2, s1, s2;
    sscanf_s(line.c_str(), "%d-%d,%d-%d", &f1, &f2, &s1, &s2);

    if(day == 1) {
        if(f1 <= s1 && f2 >= s2) totalScore += 1;
        else if(s1 <= f1 && s2 >= f2) totalScore += 1;
    }
    else {
        if(f1 <= s2 && f2 >= s1) totalScore+=1;
    }
}

void processNumbers (int day) {
    string line;
    infile.clear();
    infile.seekg(0);
    while (getline(infile, line)) {
        processLine(line, day);

    }
}

int main (void) {
    processNumbers(1);
    cout << "Day 1: " << totalScore << endl;

    totalScore = 0;
    
    processNumbers(2);
    cout << "Day 2: " << totalScore << endl;
    return 0;
}