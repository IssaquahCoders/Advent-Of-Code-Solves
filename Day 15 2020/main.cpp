#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <map>

using namespace std;
ifstream infile("data.txt");

void processLine(string line) {

}

void processData (void) {
    string line;
    while (getline(infile, line)) {
        processLine(line);
    }
}

void processIntData (void) {
    int currLoc = 7;
    int lastNum = 17;
    map<int, int> turnLocations;
    map<int, int> frequency;
    int nums[] = {0,13,1,16,6,17};
    for(int n = 0; n < 6; n++) {
        turnLocations[nums[n]] = n+1;
        frequency[nums[n]] += 1;
    }

    // Set limit depending on day (30000000 = day 2, 2020 = day 1)
    for(currLoc = 7; currLoc <= 30000000; currLoc++) {
        int tmp = lastNum;
        if(frequency[tmp] > 1) {            
            lastNum = (currLoc-1) - turnLocations[tmp];
            //cout << "LOCATION OF " << tmp << " is " << turnLocations[tmp] << " ";
            
        }
        else {
            lastNum = 0;
        }
        //cout << lastNum << endl;
        turnLocations[tmp] = currLoc-1;
        frequency[lastNum] += 1;
    }
    cout << "Day 2: " << lastNum << endl;
}

int main (void) {
    processIntData();
    return 0;
}