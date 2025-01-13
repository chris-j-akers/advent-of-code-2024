#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<sstream>
#include<algorithm>

using namespace std;

struct Position {
    int x;
    int y;
    int val;

    Position() {}
    Position(const int x, const int y, const int val) : x(x), y(y), val(val) {}

    bool operator==(Position p) {
        return (this->x == c.x) && (this->y == c.y);
    }        

    string toString() const {
        ostringstream os;
        os << "(" << this->x << "," << this->y << ")";
        return os.str();
    }

};    

class TrailMap {
    vector<vector<Position>> map;

public:
    void loadFromFile(const string inputFilePath) {
        ifstream inputFile(inputFilePath);
        string line;
        int col = 0;
        while(getline(inputFile, line)) {
            vector<Position> mapLine;
            int row = 0;
            for (char c : line) {
                mapLine.push_back(Position(row, col, );
                row++;
            }
            map.push_back(mapLine);
            col++;
        }
    }


    bool withinBounds(Position p) {
        
    }

    string toString() {

    }

};

int countTrails(Position p, int val) {
    if (c.value == 9) {
       return 1;
    }

    // Get New Co-ord
    // if within bounds and the value+1 = our current value, then call countTrails()

    if (c.value == currentTotal) {
        if ((c+1).value == c.value+1) {
            countTrails(c+1, currentTotal+1);
        }
        else {
            return 0;
        }
    }
}