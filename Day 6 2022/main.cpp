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

void processLine (string line) {
    int lp = 0, rp = 13; 
    while(rp < line.length()) {
        int n = 0;
        unordered_set<char> charSet;
        for(n = lp; n <= rp; n++) {
            if(charSet.find(line[n]) != charSet.end()) {
                break;
            }
            charSet.insert(line[n]);
        }
        if(n > rp) {
            cout << "DAY 1 OR 2 DEPENDING ON WHAT RP IS (rp = 3 is day 1 , rp = 13 is day 2): " << rp+1 << endl;
            return;
        } 
        rp++;
        lp++;
    }
}

void processNumbers (void) {
    string line;
    infile.clear();
    infile.seekg(0);
    while (getline(infile, line)) {
        processLine(line);
    }
}

int main (void) {
    processNumbers();
    return 0;
}