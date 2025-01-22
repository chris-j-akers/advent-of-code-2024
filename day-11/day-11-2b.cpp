#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<sstream>
#include<algorithm>
#include<functional>
#include <unordered_map>

using namespace std;

// Going full on recursive and read up more about memoisation - although I was 
// referring to it as Caching ... I guess, as ever, there are subtle differences, but
// it sounds the same to me.
//
// So, I wasn't *caching* the number of blinks left with the totals which was a 
// facepalm moment. If you reach a certain number, the number of blinks 
// remaining matters because the total will be different, depending on how many 
// are left! I was dumbly just inserting the value/total.


// ChatGPT wrote this hashing function for me. Whatevs. Chill out.
namespace std {
    template <>
    struct hash<pair<long, long>> {
        size_t operator()(const pair<long, long>& p) const {
            // Combine the hash of the first and second element in the pair
            size_t h1 = hash<long>()(p.first);
            size_t h2 = hash<long>()(p.second);
            // Combine the two hashes using XOR and shifting
            return h1 ^ (h2 << 1); 
        }
    };
}

// We'll use this as our cache in conjunction with the function above.
using Cache = unordered_map<pair<long, long>, long>;

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

void printStones(const vector<Stone>& stones) {
    for (Stone s : stones) {
        cout << s.val << " ";
    }
    cout << endl;
}

long blink(long val, int blinks, Cache& cache) {
    if (blinks == 0)
        return 1;

    if (cache.find(pair(val, blinks)) != cache.end()) {
        return cache[pair(val, blinks)];
    }

    string valStr = to_string(val);
    long result;
   
    if (val==0) {
        result = blink(1, blinks-1, cache);
    }    
    else if (valStr.size() % 2 == 0) {
        int operandSize = valStr.size() / 2;
        long leftTotal = blink(stol(valStr.substr(0,operandSize)), blinks-1, cache);
        long rightTotal = blink(stol(valStr.substr(operandSize,operandSize)), blinks-1, cache);
        result = leftTotal + rightTotal;
    }
    else {
        result = blink(val * 2024, blinks-1, cache);
    }

    cache[pair(val, blinks)] = result;
    return result;
}

int main() {
    vector<Stone> stones = loadStones("./input.txt");
    printStones(stones);
    cout << "\n---\n" << endl;
    Cache cache;

    long total = 0;
    for (Stone s : stones) {
        total += blink(s.val, 75, cache);
    }
    cout << total << endl;
}
