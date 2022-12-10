#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


using namespace std;

ifstream infile("data.txt");
long long int totalSum = 0;

long long int processLine (string &line, int pos, long long int sum) {
    if(pos == line.length()-1) return sum;

    long long int tempsum = 0;
    char op = '+';

    for(int n = pos; n < line.length();) {
        if(line[n] == ' ') {
            n++;
            continue;
        }
        else if(line[n] == '(') {
            if(op == '+') tempsum += processLine(line, n+1, sum);
            else if(op == '*') tempsum *= processLine(line, n+1, sum);
        }
        else if(line[n] == ')') {
            line.erase(line.begin() + n);
            return tempsum + sum;
        }
        else if( isdigit(line[n]) ) {
            if(op == '+') tempsum += line[n]-'0';
            else if(op == '*') tempsum *= line[n]-'0';
        }
        else op = line[n];

        line.erase(line.begin() + n);
    }

    return tempsum + sum;
}

void processNumbers (void) {
    string line;
    int linenumber = 1;
    while (getline(infile, line)) {
        long long int val = processLine(line, 0, 0);
        totalSum += val;
        linenumber++;
    }
}

int main (void) {
    processNumbers();
    cout << "Day 1: " << totalSum << endl;
    return 0;
}