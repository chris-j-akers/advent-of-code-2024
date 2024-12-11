#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<functional>

using namespace std;

// I think there are 332 safe reports.

bool checkLine(const vector<int> nums, const std::function<bool(int a, int b)> eval) {
    int vectorSize = nums.size();    
    int difference = 0;
    for (int i=0; i<vectorSize -1; i++) {
        difference = abs(nums[i] - nums[i+1]);
        //cout << "nums[i] = " << nums[i] << ", nums[i+1] = " << nums[i+1] << ", difference = " << difference << endl;        
        if (!(eval(nums[i], nums[i+1]) && difference > 0 && difference <= 3)) {
            return false;
        }
    }
    return true;    
}

vector<int> getVectorOfNumsFromString(string s) {
    vector<int> returnVector;    
    int startPos = 0;
    int currPos = 0;
    string levelStr;
    while(currPos < s.size()) {
        currPos = s.find(" ", startPos);
        levelStr = s.substr(startPos, currPos-startPos);        
        returnVector.push_back(stoi(levelStr));
        //cout << "[" << levelStr << "]" << ", startPos=" << startPos << ", pos=" << pos << endl;
        startPos = currPos+1;
    }
    return returnVector;
}

vector<vector<int>> loadReports(string inputFilePath) {
    ifstream inputFile(inputFilePath);
    string line;
    string num;
    vector<vector<int>> newVector;
    while (std::getline(inputFile, line)) {
        newVector.push_back(getVectorOfNumsFromString(line));
    }
    return newVector;
}

int main() {
    vector<vector<int>> reportsVector = loadReports("./input.txt");
    bool result;
    int correctResults = 0;
    for (auto levels : reportsVector) {
        if (levels[0] < levels[1]) {
            result = checkLine(levels, [](int a, int b) { return a < b; });
        } else {
            result = checkLine(levels, [](int a, int b) { return a > b; });
        }
        if (result) correctResults++;
    }

    cout << "I think there are " << correctResults << " safe reports." << endl;
}