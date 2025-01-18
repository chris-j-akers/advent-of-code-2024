#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<sstream>
#include<algorithm>
#include<functional>
#include <unordered_map>

using namespace std;

struct Stone {
    long val;
    Stone() {}
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

// Record the results of certain numbers in a hash set?

unordered_map<long, vector<long>> cache;
long cacheHit = 0;

vector<long> calculate(long val) {
    vector<long> lookup = cache[val];
    if (!lookup.empty()) {
        cacheHit++;
        return lookup;
    }
    vector<long> result;
    string valStr = to_string(val);
    if (val == 0) {
        cache[val].push_back(1);
    }
    else if (valStr.size() % 2 == 0) {
        int operandSize = valStr.size() / 2;
        cache[val].push_back(stol(valStr.substr(0,operandSize))); 
        cache[val].push_back(stol(valStr.substr(operandSize, operandSize)));
    }
    else {
        cache[val].push_back(val * 2024);
    }
    return cache[val];
}

vector<Stone> blink(const vector<Stone> oldStones) {
    vector<Stone> stones;
    for (Stone s : oldStones) {
        vector<long> result;
        result = calculate(s.val);
        for (long i : result) {
            stones.push_back(Stone(i));
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
    printStones(stones);
    for (int i=1; i<=40; i++) {
        stones = blink(stones);
        cout << i << ": " << stones.size() << ", cache hits: " << cacheHit << endl;
    }
    cout << "\n---\n" << stones.size() << endl;;    
}
