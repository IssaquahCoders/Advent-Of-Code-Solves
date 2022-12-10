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

vector<vector<int>> trees;

void processLine (string line) {
    vector<int> row;
    for(int n = 0; n < line.length(); n++) {
        row.push_back(line[n] - '0');
    }

    trees.push_back(row);
}   

void processData1 (void) {
    for(int y = 0; y < trees.size(); y++) {
        for(int x = 0; x < trees[y].size(); x++) {
            if(x == 0 || x == trees[y].size()-1 || y == 0 || y == trees.size()-1) {
                totalSum++;
                continue;
            }

            int x2 = 0, y2 = 0;
            bool directionalStates[] {true, true, true, true};

            for (x2 = 0; x2 < x; x2++) {                    
                if(trees[y][x2] >= trees[y][x]) {
                    directionalStates[0] = false;
                    break;
                }
            }

            for (x2 = x+1; x2 < trees[y].size(); x2++) {
                if(trees[y][x2] >= trees[y][x]) {
                    directionalStates[1] = false;
                    break;
                }
            }

            for (y2 = 0; y2 < y; y2++) {
                
                if(trees[y2][x] >= trees[y][x]) {
                    directionalStates[2] = false;
                    break;
                }
            }

            for (y2 = y+1; y2 < trees.size(); y2++) {
                
                if(trees[y2][x] >= trees[y][x]) {
                    directionalStates[3] = false;
                    break;
                }
            }

            for(int index = 0; index < 4; index++) {
                if(directionalStates[index]) {
                    totalSum++;
                    break;
                }
            }
        }
    }
}

void processData2 (void) {
    for(int y = 0; y < trees.size(); y++) {
        for(int x = 0; x < trees[y].size(); x++) {
            if(x == 0 || x == trees[y].size()-1 || y == 0 || y == trees.size()-1) {
                continue;
            }

            int x2 = 0, y2 = 0;
            long long int factors[] = {0, 0, 0, 0};

            for (x2 = x-1; x2 >= 0; x2--) {                    
                if(trees[y][x2] < trees[y][x]) {
                    factors[0]++;
                }
                else {
                  factors[0]++;
                  break;  
                } 
            }
            
            for (x2 = x+1; x2 < trees[y].size(); x2++) {
                if(trees[y][x2] < trees[y][x]) {
                    factors[1]++;
                }
                else {
                   factors[1]++;
                  break;  
                } 
            }

            for (y2 = y-1; y2 >= 0; y2--) {
                
                if(trees[y2][x] < trees[y][x]) {
                    factors[2]++;
                }
                else {
                   factors[2]++;
                  break;  
                } 
            }

            for (y2 = y+1; y2 < trees.size(); y2++) {
                
                if(trees[y2][x] < trees[y][x]) {
                    factors[3]++;
                }
                else {
                   factors[3]++;
                  break;  
                } 
            }    
    
            maximum = max(maximum, factors[0] * factors[1] * factors[2] * factors[3]);
        }
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
    processData1();
    processData2();

    cout << "DAY 1: " << totalSum << endl;
    cout << "DAY 2: " << maximum << endl;
    return 0;
}