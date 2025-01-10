#include <vector>
#include<fstream>
#include <iostream>
#include <sstream>
#include<unordered_set>
#include<algorithm>
#include <cstdint>


using namespace std;

// This is exactly the same as the other one but with an unordered_set instead
// of a vector to store the obstruction list. I didn't think it would make
// much difference, and it didn't - there's really not that much data, here.

// ---
// Total number of obstructions that could cause a loop: 1503
// ./a.out  59.23s user 0.00s system 99% cpu 59.240 total

vector<vector<char>> typedef Map;
enum Direction { NORTH=0, EAST=1, SOUTH=2, WEST=3 };

struct Coords {
    int x;
    int y;
    Direction direction;

    Coords(const int x, const int y, const Direction direction) : x(x), y(y), direction(direction) {}
    Coords() {}
    
    char objectAt(const Map map) const {
        char retval = map[this->y][this->x];
        return retval;
    }

    bool operator==(const Coords &c) const {
        if (this->x == c.x && this->y == c.y && this->direction == c.direction) {
            return true;
        } else {
            return false;
        }
    }

    string toString() const {
        ostringstream os;
        os << "(" << this->x << "," << this->y << ")";
        return os.str();
    }

};

struct Obstruction {
    Coords coords;
    //Direction direction;

    Obstruction() {}
    Obstruction(Coords coords) : coords(coords) {}

    bool operator==(const Obstruction &de) const {
        if (this->coords == de.coords) {
            return true;
        } 
        return false;
    }

    string toString() const {
        ostringstream os;
        os << this->coords.toString();
        return os.str();
    }

};

struct ObstructionHash {
    size_t operator()(const Obstruction ob) const 
    {
        return hash<uint32_t>()(ob.coords.x + ob.coords.y + ob.coords.direction) ^ hash<uint32_t>()(ob.coords.x + ob.coords.y + ob.coords.direction);
    }
};

struct Guard {
    vector<Coords>trail;
    unordered_set<Obstruction, ObstructionHash> obstructionList;
    Coords position;
    Coords startPosition;

    int positionCount = 1;

    Guard() {}
    Guard(const Coords position) : position(position), startPosition(position) {}

    // Starting again on each check with a new guard is slow - it always has to 
    // find the starting position which is unnecessary because it never changes.
    // We just reset the guard instead of creating a new one.
    void reset() {
        this->position = startPosition;
        obstructionList.clear();
    }

    string toString() {
        ostringstream os;
        os << position.toString() << " DUE ";
        switch(this->position.direction) {
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
        os << ", TOTAL POSITIONS: " << this->positionCount;
        return os.str();
    }

    bool jam(Map &map) {
        Coords newPosition;
        int mapWidth  = map[0].size();
        int mapLength = map.size();
        while(true) {
            switch(this->position.direction) {
                case NORTH: 
                    newPosition  = Coords(this->position.x, this->position.y -1, this->position.direction);
                    break;
                case SOUTH: 
                    newPosition  = Coords(this->position.x, this->position.y +1, this->position.direction);
                    break;
                case EAST: 
                    newPosition  = Coords(this->position.x +1, this->position.y, this->position.direction);
                    break;
                case WEST: 
                    newPosition  = Coords(this->position.x -1, this->position.y, this->position.direction);
                    break;
            }

            if (newPosition.x < 0 || newPosition.x >= mapWidth) {
                // Guard has cleared the screen
                return false;
            }

            if (newPosition.y < 0 || newPosition.y >= mapLength) {
                // Guard has cleared the screen
                return false;
            }

            if (newPosition.objectAt(map) == '#') {
                Obstruction ob = Obstruction(this->position);
                if (find(this->obstructionList.begin(), this->obstructionList.end(), ob) != this->obstructionList.end()) {
                    return true;
                } else {
                    this->obstructionList.insert(Obstruction(this->position));
                }
                this->position.direction = static_cast<Direction>(static_cast<int>(this->position.direction + 1) % 4);
                continue;
            }
            this->position = newPosition;
        }
    }

    bool patrol(Map &map) {
        Coords newPosition;
        while(true) {
            
            switch(this->position.direction) {
                case NORTH: 
                    newPosition  = Coords(this->position.x, this->position.y -1, this->position.direction);
                    break;
                case SOUTH: 
                    newPosition  = Coords(this->position.x, this->position.y +1, this->position.direction);
                    break;
                case EAST: 
                    newPosition  = Coords(this->position.x +1, this->position.y, this->position.direction);
                    break;
                case WEST: 
                    newPosition  = Coords(this->position.x -1, this->position.y, this->position.direction);
                    break;
            }

            if (newPosition.x < 0 || newPosition.x >= map[0].size()) {
                // Guard has cleared the screen
                return true;
            }

            if (newPosition.y < 0 || newPosition.y >= map.size()) {
                // Guard has cleared the screen
                return true;
            }

            if (newPosition.objectAt(map) == '#') {
                // Oof! We turn right by incrementing the enum and modulo 4! :P
                this->position.direction = static_cast<Direction>(static_cast<int>(this->position.direction + 1) % 4);
                // ...Then we recurse into the function
                return this->patrol(map);
            }

            map[this->position.y][this->position.x] = 'X';
            this->position = newPosition;
            if (newPosition.objectAt(map) != 'X') {
                this->trail.push_back(this->position);
                this->positionCount++;
            }
        }
    }
};

Coords getGuardStartPosition(const Map map) {
    int mapWidth = map[0].size();
    int mapLength = map.size();
    for (int y=0; y < mapLength; y++) {
        for (int x=0; x < mapWidth; x++) {
            if (map[y][x] == '^') {
                return Coords(x, y, NORTH);
            }
        }
    }
    return Coords(-1,-1, NORTH);
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
    Map map;
    while (getline(inputFile, line)) {
        vector<char> mapLine;
        for (char c : line) {
            mapLine.push_back(c);
        }
        map.push_back(mapLine);
    }
    return map;
}

int main() {
    Map map = loadMap("./input.txt");
    Coords startPos = getGuardStartPosition(map);
    Guard guard(getGuardStartPosition(map));

    if (guard.patrol(map) == true) {
        cout << endl << "---" << endl << "Guard made it out of the area with " << guard.positionCount << " distinct positions recorded and " << guard.trail.size() << " total positions recorded in our trail." << endl;
    }

    cout << endl << "---" << endl << "Looping time" << endl;
    cout << endl << "---" << endl;

    int obstructionCount = 0;

    // Just get the reference and make it easier to type :)
    const vector<Coords> &trail = guard.trail;
    const int trailSize = trail.size();

    // We follow the guard's previous recorded trail, dropping obstructions just
    // in-front of her. On the main input this means we only need to check just over
    // 4,454 start positions instead of a possible 116,000 if we brute-forced.

    for (int p=0; p<trailSize-1; p++) {
        Guard loopGuard(trail[p]);
        map[trail[p+1].y][trail[p+1].x] = '#';
        if (loopGuard.jam(map)) {
            //cout << "Guard at position " << trail[p].toString() << " trail index " << p << ", got stuck in loop with obstruction at: " << "(" << trail[p+1].x << "," << trail[p+1].y << ")" << ", obstructions found: " << loopGuard.obstructionList.size() << endl;
            obstructionCount++;
        }
        map[trail[p+1].y][trail[p+1].x] = '.';
    }
    cout << endl << "---" << endl << "Total number of obstructions that could cause a loop: " << obstructionCount << endl;
   
}
