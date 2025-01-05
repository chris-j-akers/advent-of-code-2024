#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<unordered_map>

using namespace std;

struct Coords {
    int x;
    int y;

    Coords() {}
    Coords(const int x, const int y) : x(x), y(y) {}

    string toString() const {
        ostringstream os;
        os << "(" << this->x << "," << this->y << ")";
        return os.str();
    }
};

unordered_map<char,vector<Coords>> typedef AntennaLookupMap;
vector<vector<char>> typedef Map;

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
    Map m;
    while(getline(inputFile, line)) {
        vector<char> mapLine;
        for (char c : line) {
            mapLine.push_back(c);
        }
        m.push_back(mapLine);
    }
    return m;
}

AntennaLookupMap buildLookupList(const Map m) {
    int mWidth = m[0].size();
    int mLength = m.size();

    AntennaLookupMap retVal;

    for (int y=0; y<mLength; y++) {
        for (int x=0; x<mWidth; x++) {
            if (m[y][x] != '.') {
                retVal[m[y][x]].push_back(Coords(x, y));
            }
        }
    }
    return retVal;
}

string antennaLookupMapToString(const AntennaLookupMap alm) {
    ostringstream os;

    for (auto al : alm) {
        os << al.first << " : ";
        for (auto c : al.second) {
            os << c.toString() << " ";
        }
        os << endl;
    }
    return os.str();
}

int main() {
    Map m = loadMap("./example.txt");
    cout << mapToString(m) << endl;
    AntennaLookupMap alm = buildLookupList(m);
    cout << antennaLookupMapToString(alm) << endl;
}