// FUNCTIONAL BUT DAY 2 IS THE MOST ATROCIOUS 
// SLOW
// UNBELIEVABLY INEFFICIENT
// SOLUTION
// ONE CAN COME UP WITH
// DO NOT RUN DAY 2

// Day 1 is just fine!

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <map>


using namespace std;
ifstream infile("data.txt");
string currentMask = "";
long long int sum = 0;
map<long long int, long long int> dataset;

void getBitRep(long long int number, int bitRep[36]) {
    int index = 35;
    while(number > 0) {
        bitRep[index--] = number % 2;
        number /= 2;
    }
}

int getMaskedValue (string line) {
    int bitRep[36];
    for(int n = 0; n < 36; n++) bitRep[n] = 0;

    long long int tempConversion = 0;

    string numRep = line.substr(line.find("=")+1);

    getBitRep(stoll(numRep), bitRep);

    cout << stoll(numRep) << "  ";
    for(int n = 0; n < 36; n++) {
        if(currentMask[n] != 'X') {
            bitRep[n] = currentMask[n] - '0';
        }
    }
    cout << " ";
    for(int n = 0; n < 36; n++) {
        cout << bitRep[n];
        tempConversion += (bitRep[n] == 1) ? pow(2, 35-n) : 0;
    }
    cout << " " << tempConversion;
    cout << endl;
    
    return tempConversion;   
}


void processLine (string line) {
    if(line.find("mask") != string::npos) {
        string maskTemp = line.substr(7);
        currentMask = maskTemp;
    }
    
    else {
        int bitRep[36];
        for(int n = 0; n < 36; n++) bitRep[n] = 0;
        string address = line.substr(line.find("[")+1, line.find("]")-line.find("["));

        long long int tempConversion = 0;

        string numRep = line.substr(line.find("=")+1);

        getBitRep(stoll(numRep), bitRep);

        for(int n = 0; n < 36; n++) {
            if(currentMask[n] != 'X') {
                bitRep[n] = currentMask[n] - '0';
            }
        }

        for(int n = 0; n < 36; n++) {
            tempConversion += (bitRep[n] == 1) ? pow(2, 35-n) : 0;
        }

        dataset[stoll(address)] = tempConversion;
    }
}

bool checkValid (string result, int bitRep[36]) {
    //cout << "RESULT: " << result << endl;
    for(int n = 0; n < result.length(); n++) {
        if(result[n] == 'X') continue;

        if(result[n]-'0' != bitRep[n])
            return false;
    }
    return true;
}

void processLine2 (string line) {
    int bitRep[36];
    string result = "000000000000000000000000000000000000";
    for(int n = 0; n < 36; n++) bitRep[n] = 0;
    if(line.find("mask") != string::npos) {
        string maskTemp = line.substr(7);
        currentMask = maskTemp;
        //cout << maskTemp << endl;
    }
    else {
        long long int tempConversion = 0;
        long long int possibility = 0;
        long long int minimum = 0;
        string address = line.substr(line.find("[")+1, line.find("]")-line.find("["));
        string numRep = line.substr(line.find("=")+1);

        getBitRep(stoll(address), bitRep);

        //cout << stoll(address) << "  ";
        for(int n = 0; n < 36; n++) {
            if(currentMask[n] == 'X') {
                possibility += pow(2, 35-n);
                result[n] = 'X';
            }
            else {
                bitRep[n] = (currentMask[n] - '0' == 1) ? 1 : bitRep[n];
                minimum += (bitRep[n] == 1) ? pow(2, 35-n) : 0;
                result[n] = bitRep[n]+'0';
            }
        }
        long long int val = stoll(numRep);
        //cout << " ";
        //long long int mval = getMaskedValue(line);
        //cout << "POSSIBLE: " << possibility << " " << "MINIMUM: " << minimum << " MASKED: " << mval << endl;
        
        // CHECKING IF EVERY. SINGLE. ADDRESS IS POSSIBLE. AGAIN, DO NOT DO THIS.
        for(int addr = minimum; addr <= possibility+minimum; addr++){
            getBitRep(addr, bitRep);
            if(checkValid(result, bitRep)) {
                //cout << "VALID: " << addr << endl;
                dataset[addr] = val;
            }
        }
    }
}


void processMasking (void) {
    string line;
    while (getline(infile, line)) {
        processLine(line);
    }
}

int main (void) {
    processMasking();
    for(auto x : dataset) {
        sum += x.second;
    }
    cout << "Day 1 (because day 2 will take hours): " << sum << endl;
    return 0;
}