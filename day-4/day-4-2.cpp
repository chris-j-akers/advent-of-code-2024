#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<functional>

using namespace std;

string wordSearchToString(const vector<vector<char>> &wordSearch) {
    ostringstream os;
    for ( auto line: wordSearch) {
        for ( auto c: line) {
            os << c << " ";
        }
        os << endl;
    }
    return os.str();
}

vector<char> getCharsFromString(const string s) {
    vector<char> returnVector;    
    int startPos = 0;
    int currPos = 0;
    char letter;
    for(char c : s) {
        returnVector.push_back(c);
    }
    return returnVector;
}

vector<vector<char>> loadWordSearch(const string inputFilePath) {
    ifstream inputFile(inputFilePath);
    string line;
    string num;
    vector<vector<char>> newWordSearch;
    while (std::getline(inputFile, line)) {
        newWordSearch.push_back(getCharsFromString(line));
    }
    return newWordSearch;
}

bool checkDiagonal(const vector<vector<char>> wordSearch, const int xStart, const int yStart, std::function<int(int n)> moveCursorHorizontal, std::function<int(int n)> moveCursorVertical) {
    cout << "Check diagonal (" << xStart << "," << yStart << "): ";
    string word = "";
    int cursorX = xStart;
    int cursorY = yStart;

    for (int charCount=0; charCount <3; charCount++) {
        word.push_back(wordSearch[cursorY][cursorX]);
        cursorX = moveCursorHorizontal(cursorX);
        cursorY = moveCursorVertical(cursorY);
    }
    cout << ": " << word << endl;
    return word == "MAS" || word == "SAM";
}

int countMAS(const vector<vector<char>> wordSearch) {
    int xLength = wordSearch.size();
    int yLength = wordSearch[0].size();
    int total = 0;
    
    for (int y=0; y < yLength; y++) {
        for(int x=0; x < xLength; x++) {
            if (x < xLength-2 && y < yLength-2) {
                if (checkDiagonal(wordSearch, x, y, [](int x){return x=x+1;}, [](int y){return y=y+1;}) && checkDiagonal(wordSearch, x+2, y, [](int x){return x=x-1;}, [](int y){return y=y+1;})) {
                    total++;
                }
            }
        }
    }
    return total;
}

int main() {
    vector<vector<char>> wordSearch = loadWordSearch("./input.txt");
    cout << wordSearchToString(wordSearch) << endl;
    cout << countMAS(wordSearch) << endl;
}