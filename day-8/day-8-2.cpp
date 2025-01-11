#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<unordered_map>
#include<algorithm>


// 390

using namespace std;

struct Coords {
    int x;
    int y;

    Coords() {}
    Coords(const int x, const int y) : x(x), y(y) {}

    Coords diff(Coords c) {
        return Coords(this->x-c.x, this->y-c.y);
    }

    Coords operator-(Coords c) {
        return Coords(this->x-c.x, this->y-c.y);
    }

    Coords operator+(Coords c) {
        return Coords(this->x+(c.x), this->y+(c.y));
    }

    bool operator==(Coords c) {
        return (this->x == c.x) && (this->y == c.y);
    }        

    string toString() const {
        ostringstream os;
        os << "(" << this->x << "," << this->y << ")";
        return os.str();
    }
};

class AntennaMap {
    vector<vector<char>> map;
    vector<Coords> antiNodes;

public:
    void loadFromFile(const string inputFilePath) {
        ifstream inputFile(inputFilePath);
        string line;
        while(getline(inputFile, line)) {
            vector<char> mapLine;
            for (char c : line) {
                mapLine.push_back(c);
            }
            map.push_back(mapLine);
        }
    }

    vector<vector<char>> getMap() const {
        return this->map;
    }

    int width() const {
        if (map.size() == 0) {
            return 0;
        }
        return map[0].size();
    }

    int length() const {
        return map.size();
    }

    int antiNodeCount() {
        return this->antiNodes.size();
    }

    string toString() const {
        ostringstream os;
        for (auto line : this->map) {
            for (auto c : line ) {
                os << c;
            }
            os << endl;
        }
        return os.str();
    }

    void draw(Coords loc, char c) {
        this->map[loc.y][loc.x] = c;
    }

    void upsertAntiNodes(Coords an) {
        if (find(this->antiNodes.begin(), this->antiNodes.end(), an) == this->antiNodes.end()) {
            this->antiNodes.push_back(an);
            this->map[an.y][an.x] = '#';
        }
    }

    bool inBounds(Coords c) const {
        return (c.x >=0 && c.y >=0) && (c.x < this->width()) && (c.y < this->length());
    }
};

class AntennaDirectory {
    unordered_map<char,vector<Coords>> directory;

public:
    AntennaDirectory(const AntennaMap m) {
        int mWidth = m.width();
        int mLength = m.length();

        for (int y=0; y<mLength; y++) {
            for (int x=0; x<mWidth; x++) {
                if (m.getMap()[y][x] != '.') {
                    directory[m.getMap()[y][x]].push_back(Coords(x, y));
                }
            }
        }
    }

    unordered_map<char,vector<Coords>> getDirectory() const {
        return this->directory;
    }

    string toString() const {
        ostringstream os;
        for (auto al : this->directory) {
            os << al.first << " : ";
            for (auto c : al.second) {
                os << c.toString() << " ";
            }
            os << endl;
        }
        return os.str();
    }
};

int main() {
    AntennaMap am;
    am.loadFromFile("./input.txt");
    cout << am.toString() << endl;
    
    AntennaDirectory ad(am);

    cout << "\n---\nPrinting antenna directory:" << endl;
    for (auto n: ad.getDirectory()) {
        cout <<"  " << n.first << ": ";
        for (auto v: n.second) {
            cout << v.toString() << " ";
        }
        cout << endl;
    }

    for (auto antenna_list: ad.getDirectory()) {
        for(auto antenna1 : antenna_list.second) {
            for (auto antenna2 : antenna_list.second) {
                if (antenna2 == antenna1) {
                    continue;
                }
                Coords diff = antenna2 - antenna1;
                Coords next = diff;
                bool inBounds = true;
                while(inBounds) {
                    Coords antiNode = antenna1 - next;
                    if (am.inBounds(antiNode)) {
                        am.upsertAntiNodes(antiNode);
                        next = next + diff;
                    } else {
                        inBounds = false;
                    }
                }
            }
            am.upsertAntiNodes(antenna1);        
        }
    }

    cout << am.toString() << endl;
    cout << "Number of anti-nodes: " << am.antiNodeCount() << endl;

}