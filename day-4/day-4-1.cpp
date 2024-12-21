#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<functional>

using namespace std;

// 2549 

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

// Moved this out just because I didn't like it being repeated in every 
// check...() function.
bool checkPattern(const string foundWord) {
    cout << "Found pattern " << foundWord;
    if (foundWord == "XMAS") {
        cout << ", returning true." << endl;
        return true;
    }
    cout << ", returning false" << endl;
    return false;
}

bool checkVertical(const vector<vector<char>> wordSearch, const int xStart, const int yStart, std::function<int(int n)> moveCursor) {
    cout << "Check vertical (" << xStart << "," << yStart << "): ";
    string foundWord = "";
    int cursor = yStart;

    for (int charCount=0; charCount <4; charCount++) {
        foundWord.push_back(wordSearch[cursor][xStart]);
        cursor = moveCursor(cursor);
    }
    return checkPattern(foundWord);
}

// We go east or west and we pass a lambda to determine which direction
bool checkHorizontal(const vector<vector<char>> wordSearch, const int xStart, const int yStart, std::function<int(int n)> moveCursor) {
    cout << "Check horizontal (" << xStart << "," << yStart << "): ";
    string foundWord = "";
    int cursor = xStart;

    for (int charCount=0; charCount <4; charCount++) {
        foundWord.push_back(wordSearch[yStart][cursor]);
        cursor = moveCursor(cursor);
    }
    return checkPattern(foundWord);
}

bool checkDiagonal(const vector<vector<char>> wordSearch, const int xStart, const int yStart, std::function<int(int n)> moveCursorHorizontal, std::function<int(int n)> moveCursorVertical) {
    cout << "Check diagonal (" << xStart << "," << yStart << "): ";
    string foundWord = "";
    int cursorX = xStart;
    int cursorY = yStart;

    for (int charCount=0; charCount <4; charCount++) {
        foundWord.push_back(wordSearch[cursorY][cursorX]);
        cursorX = moveCursorHorizontal(cursorX);
        cursorY = moveCursorVertical(cursorY);
    }
    return checkPattern(foundWord);
}

int countXMAS(const vector<vector<char>> wordSearch) {
    int xLength = wordSearch.size();
    int yLength = wordSearch[0].size();
    int total = 0;
    
    for (int y=0; y < yLength; y++) {
        for(int x=0; x < xLength; x++) {
            //Horizontally
            // L to R
            if (x+4 <= xLength && checkHorizontal(wordSearch, x, y, [](int x){return x=x+1;})) total++;

            // R to L 
            if (x-4 >=-1 && checkHorizontal(wordSearch, x, y, [](int n){return n-1;})) total++;

            // Vertically
            // T to B
            if (y + 4 <= yLength && checkVertical(wordSearch, x, y, [](int y){return y=y+1;})) total++;

            // B to T
            if (y-4 >= -1 && checkVertical(wordSearch, x, y, [](int y){return y=y-1;})) total++;

            // Diagonally
            // T to D and L to R
            if (x+4 <= xLength && y+4 <= yLength && checkDiagonal(wordSearch, x, y, [](int x){return x=x+1;}, [](int y){return y=y+1;})) total++;

            // T to D and R to L
            if (x-4 >= -1 && y+4 <= yLength && checkDiagonal(wordSearch, x, y, [](int x){return x=x-1;}, [](int y){return y=y+1;})) total++;

            // B to T and L to R
            if (x+4 <= xLength && y-4 >=-1 && checkDiagonal(wordSearch, x, y, [](int x){return x=x+1;}, [](int y){return y=y-1;})) total++;

            // B to T and R to L
            if (x-4 >= -1 && y-4 >=-1 && checkDiagonal(wordSearch, x, y, [](int x){return x=x-1;}, [](int y){return y=y-1;})) total++;
        }
    }
    return total;
}

int main() {
    vector<vector<char>> wordSearch = loadWordSearch("./input.txt");
    cout << wordSearchToString(wordSearch) << endl;
    int total = countXMAS(wordSearch);
    cout << "total: " << total << endl;
}