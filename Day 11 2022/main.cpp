#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <math.h>

using namespace std;

ifstream infile("data.txt");

class Monkey;

vector<Monkey> monkeys;
vector<vector<long long int>> listBuffer;
vector<long long int> argBuffer;
vector<vector<long long int>> argumentBuffer;
vector<char> operatorBuffer;

long long int commonDiv = 1;

class Monkey {
public:
    Monkey () {}
    Monkey (vector<long long int> starting, char op, long long int opMagnitude, 
                long long int div, long long int trueIndex, long long int falseIndex) {
        for (long long int n = 0; n < starting.size(); n++) {
            startingItems.push(starting[n]);
        }
        operationThing = op;
        operationAmnt = opMagnitude;
        divisibility = div;
        trueMonkeyOption = trueIndex;
        falseMonkeyOption = falseIndex;
    }

    Monkey (const Monkey& m) {
        startingItems = m.startingItems;
        operationThing = m.operationThing;
        operationAmnt = m.operationAmnt;
        divisibility = m.divisibility;
        trueMonkeyOption = m.trueMonkeyOption;
        falseMonkeyOption = m.falseMonkeyOption; 
    }

    long long int timesInspected = 0;
    long long int falseMonkeyOption = 0;
    long long int trueMonkeyOption = 0;
    long long int divisibility = 0;
    char operationThing = '*';
    long long int operationAmnt = 1;
    queue<long long int> startingItems;

    // Iterate through queue
    void runAllTests (int day) {
        while(!startingItems.empty()) {
            inspectTest(day);
        }
    }

    // Inspect item
    void inspectTest (int day) {
        timesInspected++;
        long long int worryLevel = startingItems.front();

        if(operationThing == '*') {
            worryLevel *= operationAmnt;
        }
        if(operationThing == '/') {
            worryLevel /= operationAmnt;
        }
        if(operationThing == '-') {
            worryLevel -= operationAmnt;
        }
        if(operationThing == '+') {
            worryLevel += operationAmnt;
        }
        if(operationThing == 'P') {
            worryLevel *= worryLevel;
        }
		
        if(day == 1)
            worryLevel = floor(worryLevel/3.0);
        if(day == 2)
            worryLevel %= commonDiv;

        if (worryLevel % divisibility == 0) {
            monkeys[trueMonkeyOption].startingItems.push(worryLevel);
        }
        else {
            monkeys[falseMonkeyOption].startingItems.push(worryLevel);
        }
        startingItems.pop();
    }
};

// Common div among divisiblity tests for part 2
long long int getCommonDiv (vector<long long int> divisors) {
    long long int product = 1;
    for (auto val : divisors) {
        product *= val;
    }
    return product;
}

// Get answer
long long int getProduct (void) {
    vector<long long int> tlist;
    for(long long int n = 0; n < monkeys.size(); n++) {
        tlist.push_back(monkeys[n].timesInspected);
    }

    sort(tlist.begin(), tlist.end());
    reverse(tlist.begin(), tlist.end());
    return tlist[0] * tlist[1];
}

// Heap allocation/requests at runtime proved troublesome, so we're going with 8 lines of bad but reliable
// instantiation code rather than requesting memory many times to avoid a possible segfault.
void runMonkeyTests (int day) {
    Monkey monkey1(listBuffer[0], operatorBuffer[0], argumentBuffer[0][0], argumentBuffer[0][1], argumentBuffer[0][2], argumentBuffer[0][3]);
    Monkey monkey2(listBuffer[1], operatorBuffer[1], argumentBuffer[1][0], argumentBuffer[1][1], argumentBuffer[1][2], argumentBuffer[1][3]);
    Monkey monkey3(listBuffer[2], operatorBuffer[2], argumentBuffer[2][0], argumentBuffer[2][1], argumentBuffer[2][2], argumentBuffer[2][3]);
    Monkey monkey4(listBuffer[3], operatorBuffer[3], argumentBuffer[3][0], argumentBuffer[3][1], argumentBuffer[3][2], argumentBuffer[3][3]);
    Monkey monkey5(listBuffer[4], operatorBuffer[4], argumentBuffer[4][0], argumentBuffer[4][1], argumentBuffer[4][2], argumentBuffer[4][3]);
    Monkey monkey6(listBuffer[5], operatorBuffer[5], argumentBuffer[5][0], argumentBuffer[5][1], argumentBuffer[5][2], argumentBuffer[5][3]);
    Monkey monkey7(listBuffer[6], operatorBuffer[6], argumentBuffer[6][0], argumentBuffer[6][1], argumentBuffer[6][2], argumentBuffer[6][3]);
    Monkey monkey8(listBuffer[7], operatorBuffer[7], argumentBuffer[7][0], argumentBuffer[7][1], argumentBuffer[7][2], argumentBuffer[7][3]);
    monkeys = {monkey1, monkey2, monkey3, monkey4, monkey5, monkey6, monkey7, monkey8};
    for(long long int x = 0; x < ((day==1)?20:10000); x++) {
        for(long long int n = 0; n < monkeys.size(); n++) {
            monkeys[n].runAllTests(day);
        }
    }
}

// All of this... for parsing the input data
vector<long long int> extractListData (string line) {
    vector<long long int> list;
    string curr = "";
    for (char c : line) {
        if(c == ' ') continue;
        if(c == ',') {
            list.push_back(stoll(curr));
            curr = "";
        }
        else {
            curr = curr + c;
        }
    }
    list.push_back(stoll(curr));
    return list;
}

void processLine (string line) {
    if(line.length() <= 1) {
        argumentBuffer.push_back(argBuffer);
        argBuffer.clear();
    }
    if(line[0] == 'M') return;

    if(line.find("Starting") != string::npos) {
        string extract = line.substr(18);
        listBuffer.push_back(extractListData(extract));
    }
    else if(line.find("Operation") != string::npos) {
        string extract = line.substr(23);
        if (extract.find("old") == string::npos) {
            int data = 0;
            char op = '*';
            operatorBuffer.push_back(extract[0]);
            sscanf(extract.c_str(), "%c %d", &op, &data);

            argBuffer.push_back(data);
        }
        else {
            operatorBuffer.push_back('P');
            argBuffer.push_back(2);
        }
    }
    else if(line.find("Test") != string::npos) {
        string extract = line.substr(21);
        argBuffer.push_back(stoll(extract));
    }
    else if(line.find("true") != string::npos) {
        string extract = line.substr(29);
        argBuffer.push_back(stoll(extract));
    }
    else if(line.find("false") != string::npos) {
        string extract = line.substr(30);
        argBuffer.push_back(stoll(extract));
    }
}

void processNumbers (void) {
    string line;
    infile.clear();
    infile.seekg(0);
    while (getline(infile, line)) {
        processLine(line);
    }
    argumentBuffer.push_back(argBuffer);
}

// Entry for actual solve
void runMonkeys (void) {
    commonDiv = getCommonDiv({argumentBuffer[0][1], argumentBuffer[1][1], argumentBuffer[2][1], 
                              argumentBuffer[3][1], argumentBuffer[4][1], argumentBuffer[5][1], 
                              argumentBuffer[6][1], argumentBuffer[7][1]});
    // Day 1
    runMonkeyTests(1);
    cout << "Day 1: " << getProduct() << endl;
    // Day 2
    runMonkeyTests(2);
    cout << "Day 2: " << getProduct() << endl;
}

int main (void) {
    processNumbers();
    runMonkeys();
    return 0;
}