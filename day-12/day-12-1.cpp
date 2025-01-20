#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<sstream>
#include<algorithm>

using namespace std;


class Garden {
    vector<vector<char>> plots;
    int plotWidth = 0;
    int plotLength = 0;

public:
    void loadPlots(const string inputFilePath) {
        ifstream inputFile(inputFilePath);
        string line;
        int row = 0;
        while(getline(inputFile, line)) {
            vector<char> mapLine;
            int col = 0;
            for (char c : line) {
                mapLine.push_back(c);
                col++;
            }
            this->plots.push_back(mapLine);
            row++;
        }
    }

    int getWidth() const {
        if (this->plots.size() == 0)
            return 0;
        else
            return this->plots[0].size();
    }

    int getLength() const {
        return this->plots.size();
    }

    string toString() const {
        ostringstream os;
        for (auto line : plots) {
            for (auto plot : line) {
                os << plot;
            }
            os << endl;
        }
        return os.str(); 
    }

    bool withinBounds(const int x, const int y) const {
        if (x >= 0 && x < this->getWidth() && y >= 0 && y < this->getLength())
            return true;
        else
            return false;
    }

    int countPlots(const char pId, const int x, const int y) const {
        if (!this->withinBounds(x, y)) {
            return 0;
        }

    }
};

int main() {
    Garden g;
    g.loadPlots("./example.txt");
    cout << g.toString() << endl;

    int result = g.countPlots('R',0,0);
    //cout << g.countPlots('R', 0, 0) << endl;
}