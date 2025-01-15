#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<sstream>
#include<algorithm>

using namespace std;

/* Brilliantly, because I'd misread the question in part 1 and already used recursion
to count the trails, I'd already done part 2. This was just a case of adding
up the return value from countTrails() instead of the unique 9s */

struct Position {
    int x;
    int y;
    int val;

    Position() {}
    Position(const int x, const int y, const int val) : x(x), y(y), val(val) {}

    bool operator==(Position p) const {
        return this->x == p.x && this->y == p.y && this->val == p.val;
    }

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
                mapLine.push_back(Position(col, row, c -'0' ));
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
    
    bool withinBounds(const int x, const int y) const {
        if (x >= 0 && x < this->getWidth() && y >= 0 && y < this->getLength())
            return true;
        else
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

    vector<Position> getTrailHeads(const int startVal) const {
        vector<Position> trailHeads;
        for (auto row : this->map) {
            for (auto col : row) {
                if (col.val == startVal)
                    trailHeads.push_back(col);
            }
        }
        return trailHeads;
    }

    int countTrails(const int x, const int y, const int reqVal, vector<Position>& endPositions) const {
        if (!this->withinBounds(x,y)) {
            return 0;
        }

        if (reqVal == 9 && this->map[y][x].val == 9) {
            if (find(endPositions.begin(), endPositions.end(), this->map[y][x]) == endPositions.end()) {
                endPositions.push_back(this->map[y][x]);
            }
            return 1;
        }

        if (this->map[y][x].val == reqVal) {
            return 
                // North
                countTrails(x, y-1, reqVal+1, endPositions) +
                // South
                countTrails(x, y+1, reqVal+1, endPositions) +
                // East
                countTrails(x+1 ,y, reqVal+1, endPositions) +
                // West
                countTrails(x-1, y, reqVal+1, endPositions);
        }
        else {
            return 0;
        }
    }
};

int main() {
    TrailMap tm;
    
    tm.loadFromFile("./input.txt");
    cout << tm.toString() << endl;

    vector<Position> trailHeads = tm.getTrailHeads(0);
    vector<Position> endPositions;

    int score = 0;
    for (auto th : trailHeads) {
        int availableTrails = tm.countTrails(th.x, th.y, 0, endPositions);
        if (availableTrails > 0) {
            int numberOfEndPositions = endPositions.size();
            cout << "Trail head " << th.toString() << " can reach " << availableTrails << " stage 9s, ";
            cout << numberOfEndPositions << " of which are unique." << endl;
            score += availableTrails;
        }
        endPositions.clear();
    }
    cout << "\n---\n" << "Total score for this map is: " << score << endl;
}

