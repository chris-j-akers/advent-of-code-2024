#include <vector>
#include<fstream>
#include <iostream>
#include <sstream>
#include<algorithm>

using namespace std;

// Right, right, right. I'm thinking we don't always need to start the guard in 
// the same position? Because if we know her path is clear up to the obstruction
// then we don't need her to walk it. How about we always start the guard one
// position begin the obstruction!?!?!?

vector<vector<char>> typedef Map;
enum Direction { NORTH=0, EAST=1, SOUTH=2, WEST=3 };

struct Coords {
    int x;
    int y;
    Direction direction;

    Coords(const int x, const int y, const Direction direction) : x(x), y(y), direction(direction) {}
    Coords() {}
    
    char objectAt(const Map map) {
        char retval = map[this->y][this->x];
        return retval;
    }

    bool operator==(const Coords &c) {
        if (this->x == c.x && this->y == c.y && this->direction == c.direction) {
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
    //Direction direction;

    Obstruction() {}
    Obstruction(Coords coords) : coords(coords) {}

    bool operator==(const Obstruction &de) {
        if (this->coords == de.coords) {
            return true;
        } else {
            return false;
        }
    }

    string toString() {
        ostringstream os;
        os << this->coords.toString();
        return os.str();
    }

} typedef Obstruction;

struct Guard {
    vector<Coords>trail;
    vector<Obstruction> obstructionList;
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
                return false;
            }

            if (newPosition.y < 0 || newPosition.y >= map.size()) {
                // Guard has cleared the screen
                return false;
            }

            if (newPosition.objectAt(map) == '#') {
                Obstruction ob = Obstruction(this->position);
                if (find(this->obstructionList.begin(), this->obstructionList.end(), ob) != this->obstructionList.end()) {
                    return true;
                } else {
                    this->obstructionList.push_back(Obstruction(this->position));
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

int main() {
    Map map = loadMap("./input.txt");
    Coords startPos = getGuardStartPosition(map);
    Guard g(getGuardStartPosition(map));

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
