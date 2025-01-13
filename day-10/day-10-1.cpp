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

    string toString() const {
        ostringstream os;
        os << "[" << this->val << ":(" << this->x << "," << this->y << ")]";
        return os.str();
    }
};    

class TrailMap {
    vector<vector<Position>> map;

public:
    void loadFromFile(const string inputFilePath) {
        ifstream inputFile(inputFilePath);
        string line;
        int row = 0;
        while(getline(inputFile, line)) {
            vector<Position> mapLine;
            int col = 0;
            for (char c : line) {
                mapLine.push_back(Position(row, col, c -'0' ));
                col++;
            }
            map.push_back(mapLine);
            row++;
        }
    }

    int getWidth() const {
        if (this->map.size() == 0)
            return 0;
        else
            return this->map[0].size();
    }

    int getLength() const {
        return this->map.size();
    }
    
    bool withinBounds(const Position p) const {
        return false;
    }

    string toString() const {
        int mapLength = this->getLength();
        int mapWidth = this->getWidth();

        ostringstream os;
        for (int row=0; row < mapLength; row++) {
            for (int col=0; col < mapWidth; col++) {
                os << this->map[row][col].toString();
            }
            os << endl;
        }
        return os.str();
    }

    vector<Position> getValidStartPositions(const int startVal) const {
        vector<Position> startPositions;
        for (auto row : this->map) {
            for (auto col : row) {
                if (col.val == startVal)
                    startPositions.push_back(col);
            }
        }
        return startPositions;
    }
};

int main() {
    TrailMap tm;
    tm.loadFromFile("./example.txt");
    cout << tm.toString() << endl;
    vector<Position> startPositions = tm.getValidStartPositions(1);

    for (auto p: startPositions)
        cout << p.toString();
    cout << endl;
}

// Only call this if the current value is 1.
// Pull a list of all 1s from the map and call countTrails on each one.

// int countTrails(Position p, int val) {
//     if (c.value == 9) {
//        return 1;
//     }

//     // Get New Co-ord
//     // if within bounds and the value+1 = our current value, then call countTrails()

//     if (c.value == currentTotal) {
//         if ((c+1).value == c.value+1) {
//             countTrails(c+1, currentTotal+1);
//         }
//         else {
//             return 0;
//         }
//     }
// }

