#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<sstream>
#include<algorithm>

using namespace std;

struct Coords {
    int x;
    int y;

    Coords(const int x, const int y) : x(x), y(y) {}
    Coords() {}
    
    char objectAt(const vector<vector<char>> plots) {
        char retval = plots[this->y][this->x];
        return retval;
    }

    string toString() {
        ostringstream os;
        os << "(" << this->x << "," << this->y << ")";
        return os.str();
    }

    bool operator==(const Coords c) {
        return this->x==c.x && this->y==c.y;
    }

};

struct Region {
    char id;
    int area;
    int perimeter;
};

class Garden {
    vector<vector<char>> plots;
    vector<char> regionList;
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

    bool withinBounds(const Coords c) const {
        if (c.x >= 0 && c.x < this->getWidth() && c.y >= 0 && c.y < this->getLength())
            return true;
        else
            return false;
    }

    int countPlots(const char plotId, const Coords c, vector<Coords>& plotsVisited) const {
        if (!this->withinBounds(c)) {
            return 0;
        }        

        if (find(plotsVisited.begin(), plotsVisited.end(), c) != plotsVisited.end())
            return 0;

        if (this->plots[c.y][c.x] == plotId) {
            // If we don't do this, the thing goes on forever revisiting
            // old plots.
            plotsVisited.push_back(Coords(c.x,c.y));
            return 1 +
                // North
                countPlots(plotId, Coords(c.x, c.y-1), plotsVisited) +
                // South
                countPlots(plotId, Coords(c.x, c.y+1), plotsVisited) +
                // East
                countPlots(plotId, Coords(c.x+1, c.y), plotsVisited) +
                // West
                countPlots(plotId, Coords(c.x-1, c.y), plotsVisited);
        }
        else {
            // So the previous x,y was a perimeter?
            return 0;
        }
    }
    
};

int main() {
    Garden g;
    g.loadPlots("./example.txt");
    cout << g.toString() << endl;
    vector<Coords> plotsVisited;

    cout << "Beginning plot is: " << startPlot.toString() << endl;
    int result = g.countPlots('E', startPlot, plotsVisited);
    cout << result << endl;
    //cout << g.countPlots('R', 0, 0) << endl;
}