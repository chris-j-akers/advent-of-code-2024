#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<sstream>
#include<algorithm>
#include<functional>
#include <unordered_map>

using namespace std;

// Gotta feeling this needs a different DataStructure

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


void printStones(const vector<Stone>& stones) {
    for (Stone s : stones) {
        cout << s.val << " ";
    }
    cout << endl;
}


// vector<long> calculate(long val) {
//     vector<long> lookup = cache[val];
//     if (!lookup.empty()) {
//         cacheHit++;
//         return lookup;
//     }
//     vector<long> result;
//     string valStr = to_string(val);
//     if (val == 0) {
//         cache[val].push_back(1);
//     }
//     else if (valStr.size() % 2 == 0) {
//         int operandSize = valStr.size() / 2;
//         cache[val].push_back(stol(valStr.substr(0,operandSize))); 
//         cache[val].push_back(stol(valStr.substr(operandSize, operandSize)));
//     }
//     else {
//         cache[val].push_back(val * 2024);
//     }
//     return cache[val];
// }

long blink(long val, long total, int blinkCounter, const int maxBlinks) {
    // cout << "[" << blinkCounter << "]" << endl;;
    if (blinkCounter > maxBlinks)
        return total;
    
    if (val==0) {
        return blink(1, total, blinkCounter+1, maxBlinks);
    }

    string valStr = to_string(val);
    if (valStr.size() % 2 == 0) {
        int operandSize = valStr.size() / 2;
        long leftTotal = blink(stol(valStr.substr(0,operandSize)), total, blinkCounter+1, maxBlinks);
        long rightTotal = blink(stol(valStr.substr(operandSize,operandSize)), total, blinkCounter+1, maxBlinks);
        //cout << "Left: " << leftTotal << ", right: " << rightTotal << endl;
        return (leftTotal + rightTotal)+1;
    }
    return blink(val * 2024, total, blinkCounter+1, maxBlinks);
}

// 125 = 7
// 17 = 15

int main() {
    vector<Stone> stones = loadStones("./input.txt");
    printStones(stones);
    cout << "\n---\n" << endl;

    long total = 0;
    for (Stone s : stones) {
        total += blink(s.val, 0, 1, 30) + 1;
    }
    cout << total << endl;
}
