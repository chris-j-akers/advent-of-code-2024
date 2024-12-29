#include <vector>
#include<fstream>
#include <iostream>
#include <sstream>
#include<algorithm>

// Brute-force so very slow. There's no real need to drop obstacles outside of
// the security guard's path which is the mistake I'm making, here. But left in
// for posterity.

using namespace std;

// Let's get a little more domain-oriented
vector<vector<char>> typedef Map;

enum Direction { NORTH=0, EAST=1, SOUTH=2, WEST=3 };

struct Coords {
    int x;
    int y;

    Coords() {}
    Coords(const int x, const int y) : x(x), y(y) {}
    
    char objectAt(const Map map) {
        char retval = map[this->y][this->x];
        return retval;
    }

    bool operator==(const Coords &c) {
        if (this->x == c.x && this->y == c.y) {
            return true;
        } else {
            return false;
        }
    }

    string toString() {
        ostringstream os;
        os << "(" << this->x << "," << this->y << ")";
        return os.str();
    }

} typedef Coords;

struct Obstruction {
    Coords coords;
    Direction direction;

    Obstruction() {}
    Obstruction(Coords coords, Direction direction) : coords(coords), direction(direction) {}

    bool operator==(const Obstruction &de) {
        if (this->coords == de.coords && this->direction == de.direction) {
            return true;
        } else {
            return false;
        }
    }

    string toString() {
        ostringstream os;
        os << this->coords.toString() << ", " << this->direction;
        return os.str();
    }

} typedef Obstruction;

struct Guard {
    Coords position;
    Coords startPosition;

    Direction direction;
    Direction startDirection;
    
    vector<Obstruction> obstructionList;

    Guard() {}
    Guard(const Coords position, const Direction direction) : position(position), startPosition(position), direction(direction), startDirection(direction) {}

    // Starting again on each check with a new guard is slow - it always has to 
    // find the starting position which is unnecessary because it never changes.
    // We just reset the guard instead of creating a new one.
    void reset() {
        this->position = startPosition;
        this->direction = startDirection;
        obstructionList.clear();
    }

    string toString() {
        ostringstream os;
        os << position.toString() << " FACING DUE ";
        switch(this->direction) {
            case NORTH:
                os << "NORTH";
                break;
            case SOUTH:
                os << "SOUTH";
                break;
            case EAST:
                os << "EAST";
                break;
            case WEST:
                os << "WEST";
                break;
        }
        return os.str();
    }

    bool patrol(Map &map) {
        Coords newPosition;
        while(true) {
            switch(this->direction) {
                case NORTH: 
                    newPosition  = Coords(this->position.x, this->position.y -1);
                    break;
                case SOUTH: 
                    newPosition  = Coords(this->position.x, this->position.y +1);
                    break;
                case EAST: 
                    newPosition  = Coords(this->position.x +1, this->position.y);
                    break;
                case WEST: 
                    newPosition  = Coords(this->position.x -1, this->position.y);
                    break;
            }

            if (newPosition.x < 0 || newPosition.x >= map[0].size()) {
                // Guard has cleared the screen
                return false;
            }

            if (newPosition.y < 0 || newPosition.y >= map.size()) {
                // Guard has cleared the screen
                return false;
            }

            if (newPosition.objectAt(map) == '#') {
                // Has this obstruction already been encountered?
                Obstruction ob(newPosition, this->direction);
                if (find(obstructionList.begin(), obstructionList.end(), ob) != obstructionList.end()) {
                    return true;
                }

                obstructionList.push_back(ob);
                // Oof! We turn right by incrementing the enum and modulo 4! :P
                this->direction = static_cast<Direction>(static_cast<int>(this->direction + 1) % 4);
                //... Then back to top of loop
                continue;
            }
            this->position = newPosition;
        }
    }
};

Coords getGuardStartPosition(const Map map) {
    int mapWidth = map[0].size();
    int mapLength = map.size();
    for (int y=0; y < mapLength; y++) {
        for (int x=0; x < mapWidth; x++) {
            if (map[y][x] == '^') {
                return Coords(x, y);
            }
        }
    }
    return Coords(-1,-1);
}

string mapToString(const Map map) {
    ostringstream os;
    for (auto line : map) {
        for (auto c : line ) {
            os << c;
        }
        os << endl;
    }
    return os.str();
}

Map loadMap(const string inputFilePath) {
    ifstream inputFile(inputFilePath);
    string line;
    vector<vector<char>> map;
    while (getline(inputFile, line)) {
        vector<char> mapLine;
        for (char c : line) {
            mapLine.push_back(c);
        }
        map.push_back(mapLine);
    }
    return map;
}

// Utility function for tracingg/debugging
void printObstructionList(const vector<Obstruction> &obList) {
    cout << "List of obstructions: " << endl;
    for (Obstruction o : obList) {
        cout << o.toString() << endl;
    }
}

int main() {
    Map map = loadMap("./input.txt");
    int mapWidth = map[0].size();
    int mapLength = map.size();

    int obstructionCount = 0;

    Guard g(getGuardStartPosition(map), NORTH);
    for (int y=0; y<mapLength; y++) {
        for (int x=0; x<mapWidth; x++) {
            g.reset();
            if (map[y][x] == '.') {
                map[y][x] = '#';
                if (!g.patrol(map)) {
                    cout << "Guard exited map with obstruction at: " << "(" << x << "," << y << ")" << ", obstructions found: " << g.obstructionList.size() << endl;
                } else {
                    cout << "Guard got stuck in loop with obstruction at: " << "(" << x << "," << y << ")" << ", obstructions found: " << g.obstructionList.size() << endl;
                    obstructionCount++;
                }
                map[y][x] = '.';
            }
        }
    }
    cout << endl << "---" << endl << "Total number of obstructions that could cause a loop: " << obstructionCount << endl;
}
