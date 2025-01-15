#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<sstream>
#include<algorithm>

using namespace std;

struct Stone {
    long val;

    Stone(long val) : val(val) {}
};

vector<Stone> loadStones(const string inputFilePath) {
    vector<Stone> stones;
    ifstream inputFile(inputFilePath);
    string line;
    while(getline(inputFile, line, ' ')) {
        stones.push_back(Stone(stol(line)));
    }
    return stones;
}

vector<Stone> blink(const vector<Stone> oldStones) {
    vector<Stone> stones;
    for (Stone s : oldStones) {
        string valStr = to_string(s.val);
        if (s.val == 0) {
            stones.push_back(1);
        }
        else if (valStr.size() % 2 == 0) {
            int operandSize = valStr.size() / 2;
            stones.push_back(stol(valStr.substr(0,operandSize)));
            stones.push_back(stol(valStr.substr(operandSize, operandSize)));
        }
        else {
            stones.push_back(s.val * 2024);
        }
    }
    return stones;
}

void printStones(const vector<Stone>& stones) {
    for (Stone s : stones) {
        cout << s.val << " ";
    }
    cout << endl;
}

int main() {
    vector<Stone> stones = loadStones("./input.txt");
    for (int i=1; i<=50; i++) {
        stones = blink(stones);
        cout << i << ": " << stones.size() << endl;;
    }
    //printStones(stones);
}
