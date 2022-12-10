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

void processLine (string line) {
    int currScore = 0;
    char shit = line[0];
    char shit2 = line[2];

    if(shit2 == 'Y') {
        currScore = 2;
        if(shit == 'A') {
            currScore += 6;
        }
        else if(shit == 'B') currScore += 3;
    }

    if(shit2 == 'Z') {
        currScore = 3;
        if(shit == 'B') {
            currScore += 6;
        }
        else if(shit == 'C') currScore += 3;
    }

    if(shit2 == 'X') {
        currScore = 1;
        if(shit == 'C') {
            currScore += 6;
        }
        else if(shit == 'A') currScore += 3;
    }
    totalScore += currScore;
}

void processLine2 (string line) {
    int currScore = 0;
    char shit = line[0];
    char shit2 = line[2];  

    if(shit2 == 'X') {
        if(shit == 'A') {
            currScore += 3;
        }
        if(shit == 'B') {
            currScore += 1;
        }
        if(shit == 'C') {
            currScore += 2;
        }
    }

    if(shit2 == 'Y') {
        if(shit == 'A') {
            currScore += 4;
        }
        if(shit == 'B') {
            currScore += 5;
        }
        if(shit == 'C') {
            currScore += 6;
        }
    }

    if(shit2 == 'Z') {
        if(shit == 'A') {
            currScore += 8;
        }
        if(shit == 'B') {
            currScore += 9;
        }
        if(shit == 'C') {
            currScore += 7;
        }
    }
    totalScore += currScore;
}

void processNumbers (int day) {
    string line;
    infile.clear();
    infile.seekg(0);
    while (getline(infile, line) && !checked) {
        if(day == 1) processLine(line);
        else processLine2(line);
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