#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <string>

using namespace std;

ifstream infile("data.txt");
long long int totalSum = 0;
long long int maximum = INT_MIN;
vector<int> list;

void processLine (string line) {
    if(line.length()  <= 0) {
        maximum = max(totalSum, maximum);
        list.push_back(totalSum);
        totalSum = 0;
        return;
    }

    long long int val = stoll(line);
    totalSum += val;
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
    sort(list.begin(), list.end());
    cout << "Day 1: " << maximum << endl;
    cout << "Day 2: " << list[list.size()-1] + list[list.size()-2] + list[list.size()-3] << endl;
    return 0;
}