#include <vector>
#include<fstream>
#include <iostream>
#include <sstream>
#include<algorithm>

using namespace std;

// Gives right answer, but v. slow. (though much better than earlier brute-force attempt).
// Seen on the interwebs that people have managed to do this in 20ms or so.
// Will have another think. I can't believe the vector of obstructions is the
// issue because there's not much in them.

// Let's get a little more domain-oriented
using Map = vector<vector<char>>;
enum Direction { NORTH=0, EAST=1, SOUTH=2, WEST=3 };

struct Coords {
    int x;
    int y;

    Coords(const int x, const int y) : x(x), y(y) {}
    Coords() {}
    
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

};

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

};

struct Guard {
    vector<Coords>trail;
    vector<Obstruction> obstructionList;
    Coords position;
    Coords startPosition;

    Direction direction;
    Direction startDirection;

    int positionCount = 1;

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
        os << position.toString() << " DUE ";
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
        os << ", TOTAL POSITIONS: " << this->positionCount;
        return os.str();
    }

    bool jam(Map &map) {
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
                Obstruction ob = Obstruction(this->position, this->direction);
                if (find(this->obstructionList.cbegin(), this->obstructionList.cend(), ob) != this->obstructionList.cend()) {
                    return true;
                } else {
                    this->obstructionList.push_back(Obstruction(this->position, this->direction));
                }
                this->direction = static_cast<Direction>(static_cast<int>(this->direction + 1) % 4);
                continue;
            }
            this->position = newPosition;
        }
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
                return true;
            }

            if (newPosition.y < 0 || newPosition.y >= map.size()) {
                // Guard has cleared the screen
                return true;
            }

            if (newPosition.objectAt(map) == '#') {
                // Oof! We turn right by incrementing the enum and modulo 4! :P
                this->direction = static_cast<Direction>(static_cast<int>(this->direction + 1) % 4);
                // ...Then we recurse into the function
                return this->patrol(map);
            }

            map[this->position.y][this->position.x] = 'X';
            this->position = newPosition;
            if (newPosition.objectAt(map) != 'X') {
                this->positionCount++;
                this->trail.push_back(this->position);
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
    Guard g(getGuardStartPosition(map), NORTH);

    if (g.patrol(map) == true) {
        cout << "Guard made it out of the area with " << g.positionCount << " positions recorded. Now we're going to try and jam her." << endl;
    }

    int obstructionCount = 0;
    for (Coords footstep : g.trail) {
        g.reset();
        map[footstep.y][footstep.x] = '#';
            if (g.jam(map)) {
                cout << "Guard got stuck in loop with obstruction at: " << "(" << footstep.x << "," << footstep.y << ")" << ", obstructions found: " << g.obstructionList.size() << endl;
                obstructionCount++;
            }
            map[footstep.y][footstep.x] = '.';
    }
    cout << endl << "---" << endl << "Total number of obstructions that could cause a loop: " << obstructionCount << endl;
   
}
