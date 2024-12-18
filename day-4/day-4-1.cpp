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

bool checkNorth(const vector<vector<char>> wordSearch, const int xStart, const int yStart) {
    cout << "Check North (" << yStart << "," << xStart << ")" << endl;           
    if (yStart < 3) return 0;
    string xmas = "";
    int charCount = 0;
    for (int y = yStart; charCount <4; y--) {
        xmas.push_back(wordSearch[y][xStart]);
        charCount++;
    }
    cout << "  Found pattern: " << xmas;
    if (xmas == "XMAS") {
        cout << ", returning true." << endl;
        return true;
    }
    cout << ", returning false" << endl;
    return false;
}



bool checkSouth(const vector<vector<char>> wordSearch, const int xStart, const int yStart) {
    if (yStart > 6) return 0;
    string xmas = "";
    int charCount = 0;
    for (int y = yStart; charCount <4; y++) {
        cout << "cords (" << y << ", " << xStart << ")" << ": " << wordSearch[y][xStart] << endl;
        xmas.push_back(wordSearch[y][xStart]);
        charCount++;
    }
    cout << "Found pattern: " << xmas;
    if (xmas == "XMAS") {
        cout << ", returning true." << endl;
        return true;
    }
    cout << ", returning false" << endl;
    return false;
}

int incX(int x) {
    return x++;
}

bool checkEast(const vector<vector<char>> wordSearch, const int xStart, const int yStart, std::function<int>f(int n)) {
    cout << "Check East (" << yStart << "," << xStart << ")" << endl;
    if (xStart > 6) return 0;
    string xmas = "";
    int charCount = 0;
    for (int x = xStart; charCount <4; incX(x)) {
        cout << "cords (" << yStart << ", " << x << ")" << ": " << wordSearch[yStart][x] << endl;
        xmas.push_back(wordSearch[yStart][x]);
        charCount++;
    }
    cout << "\tFound pattern: " << xmas;
    if (xmas == "XMAS") {
        cout << ", returning true." << endl;
        return true;
    }
    cout << ", returning false" << endl;
    return false;
}


bool checkWest(const vector<vector<char>> wordSearch, const int xStart, const int yStart, std::function<int(int n)> f) {
    cout << "Check West (" << yStart << "," << xStart << ")" << endl;    
    if (xStart < 3) return 0;
    string xmas = "";
    int charCount = 0;
    for (int x = xStart; charCount <4; x = f(x)) {
        xmas.push_back(wordSearch[yStart][x]);
        charCount++;
    }
    cout << "  Found pattern: " << xmas;
    if (xmas == "XMAS") {
        cout << ", returning true." << endl;
        return true;
    }
    cout << ", returning false" << endl;
    return false;
}

int countXMAS(const vector<vector<char>> wordSearch) {
    int xLength = wordSearch.size();
    int yLength = wordSearch[0].size();
    int total = 0;
    for (int y=0; y < yLength; y++) {
        for(int x=0; x < xLength; x++) {

            //cout << "cords (" << x << ", " << y << ")" << endl;
            // cout << "Checking North" << endl;
            //total += checkNorth(wordSearch, x,y);
            total += checkWest(wordSearch, x,y, [](int n){return n=n-1;});                 
            // cout << "Checking South" << endl;
            // total += checkSouth(wordSearch, x,y);
            // // cout << "Checking East" << endl;
            // total += checkSouth(wordSearch, x,y);
                   

        }
    }
    return total;
}

int main() {
    vector<vector<char>> wordSearch = loadWordSearch("./example.txt");
    cout << wordSearchToString(wordSearch) << endl;
    int total = countXMAS(wordSearch);
    cout << "total: " << total << endl;
}