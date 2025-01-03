#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>

using namespace std;

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

int main() {
    Map m = loadMap("./example.txt");
    cout << mapToString(m) << endl;

}