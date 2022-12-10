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
void processLine (string line) {
    int n = 0;
    unordered_set<char> firstComp;
    char reoc;

    for(n = 0; n < line.length() / 2; n++) {
        firstComp.insert(line[n]);
    }
    for(n; n < line.length(); n++) {
        if(firstComp.find(line[n]) != firstComp.end()) {
            reoc = line[n];
        }
    }

    int position = (isupper(reoc)) ? tolower(reoc) - 'a' + 27 : reoc - 'a' + 1;

    cout << position << endl;
    totalScore += position;
}

char getCommon (string l1, string l2, string l3) {
    for(int n1 = 0; n1 < l1.length(); n1++) {
        char curr = l1[n1];
        for(int n2 = 0; n2 < l2.length(); n2++) {
            if(curr == l2[n2]) {
                for(int n3 = 0; n3 < l3.length(); n3++) {
                    if(curr == l3[n3]) return curr;
                }
            }
        }
    }
}

void processLine2 (string line, int c) {
    myStrings[c] = line;
}

void processNumbers (void) {
    string line;
    infile.clear();
    infile.seekg(0);
    while (getline(infile, line)) {
        processLine2(line, 0);
        getline(infile, line);
        processLine2(line, 1);
        getline(infile, line);
        processLine2(line, 2);

        char x = getCommon(myStrings[0], myStrings[1], myStrings[2]);
        int position = (isupper(x)) ? tolower(x) - 'a' + 27 : x - 'a' + 1; 

        totalScore += position;
    }
}

int main (void) {
    processNumbers();
    cout << "Day 2: " << totalScore << endl;
    return 0;
}