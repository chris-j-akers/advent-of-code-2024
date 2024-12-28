#include <vector>
#include<fstream>
#include <iostream>
#include <sstream>

using namespace std;

// Let's get a little more domain-oriented
vector<vector<char>> typedef Map;
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

    string toString() {
        ostringstream os;
        os << "(" << this->x << "," << this->y << ")";
        return os.str();
    }

} typedef Coords;
struct Guard {
    Coords position;
    Direction direction;
    int positionCount = 1;

    Guard() {}
    Guard(const Coords position, const Direction direction) : position(position), direction(direction) {}

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

    bool move(Map &map) {
        Coords newPosition;
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
            return this->move(map);
        }

        map[this->position.y][this->position.x] = 'X';
        this->position = newPosition;
        if (newPosition.objectAt(map) != 'X') positionCount++;
        return false;
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

int main() {
    Map map = loadMap("./input.txt");
    Coords startPos = getGuardStartPosition(map);
    Guard g(getGuardStartPosition(map), NORTH);

    cout << g.toString() << endl;
    cout << mapToString(map) << endl;
    cout << "----------" << endl << endl;

    while(g.move(map) != true) {
        cout << g.toString() << endl;
    }
    cout << "OUT OF AREA!" << endl;
}
