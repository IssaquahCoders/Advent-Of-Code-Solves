#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <string>
#include <map>

using namespace std;

ifstream infile("data.txt");
long long int totalSum = 0;

int currCycle = 1;
int registerValue = 1;
bool cycleComplete = false;
map<int, int> cycleMap;

void processLine (string line) {
    string cmd = line.substr(0, 4);
    if(cmd == "noop") {
        cycleMap[currCycle++] = registerValue;
    }
    else if(cmd == "addx") { 
        cycleMap[currCycle++] = registerValue; 
        string data = line.substr(4);
        registerValue += stoi(data);
        cycleMap[currCycle++] = registerValue;
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

long long int getSignalStrength(long long int cycle) {
    return (cycle+1) * cycleMap[cycle];
}

int main (void) {
    processNumbers();
    cout << "Day 1: ";
    cout << getSignalStrength(19) + getSignalStrength(59) + getSignalStrength(99) + getSignalStrength(139) + getSignalStrength(179) + getSignalStrength(219) << endl;
    return 0;
}