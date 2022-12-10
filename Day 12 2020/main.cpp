#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>


using namespace std;
char currDirection = 'E';
int xcoord = 0, ycoord = 0;
int wayX = 10, wayY = 1;
vector<char> directionArr = {'E', 'S', 'W', 'N'};
ifstream infile("data.txt");

void processCardinal(char instruction, int data) {
    if(instruction == 'N') {
        ycoord += data;
    }
    else if(instruction == 'S') {
        ycoord -= data;
    }
    else if(instruction == 'E') {
        xcoord += data;
    }
    else if(instruction == 'W') {
        xcoord -= data;
    }
}

void processLine (string line) {
    char instruction = line[0];

    line.erase(line.begin());

    int data = stoi(line);

    if(instruction == 'L') {
        currDirection = directionArr[4 - ((data / 90) % 4)];
        while(directionArr[0] != currDirection) {
            rotate(directionArr.begin(), directionArr.end() - 1, directionArr.end());
        }      
    }
    else if(instruction == 'R') {
        currDirection = directionArr[(data / 90) % 4];
        while(directionArr[0] != currDirection) {
            rotate(directionArr.begin(), directionArr.end() - 1, directionArr.end());
        }
    }
    else if(instruction == 'F') {
        processCardinal(currDirection, data);
    }
    else processCardinal(instruction, data);
}

void processCardinal2(char instruction, int data) {
    if(instruction == 'N') {
        wayY += data;
    }
    else if(instruction == 'S') {
        wayY -= data;
    }
    else if(instruction == 'E') {
        wayX += data;
    }
    else if(instruction == 'W') {
        wayX -= data;
    }
}

void processLineTwo (string line) {
    char instruction = line[0];

    line.erase(line.begin());

    int data = stoi(line);

    if(instruction == 'L') {
        if(data == 90) {
            swap(wayX, wayY);
            wayX = -wayX;
        }
        if(data == 180) {
            wayX = -wayX;
            wayY = -wayY;
        }
        if(data == 270) {
            swap(wayX, wayY);
            wayY = -wayY;
        }
    }
    else if(instruction == 'R') {
        if(data == 90) {
            swap(wayX, wayY);
            wayY = -wayY;
        }
        if(data == 180) {
            wayX = -wayX;
            wayY = -wayY;
        }
        if(data == 270) {
            swap(wayX, wayY);
            wayX = -wayX;
        }
    }
    else if(instruction == 'F') {
        xcoord += data*wayX;
        ycoord += data*wayY;
    }
    else processCardinal2(instruction, data);
}

void processDirections (int day) {
    string line;
    infile.clear();
    infile.seekg(0);
    while (getline(infile, line)) {
        if(day == 2) processLineTwo(line);
        else processLine(line);
    }
}

int main (void) {
    processDirections(1);
    cout << "Day 1: " << abs(ycoord) + abs(xcoord) << endl;
    ycoord = xcoord = 0;

    processDirections(2);
    cout << "Day 2: " << abs(ycoord) + abs(xcoord) << endl;
    return 0;
}