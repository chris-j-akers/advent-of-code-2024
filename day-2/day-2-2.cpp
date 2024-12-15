#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<functional>

using namespace std;

// I think there are 332 safe reports.

vector<int> getVectorOfNumsFromString(const string s) {
    vector<int> returnVector;    
    int startPos = 0;
    int currPos = 0;
    string levelStr;
    while(currPos < s.size()) {
        currPos = s.find(" ", startPos);
        levelStr = s.substr(startPos, currPos-startPos);        
        returnVector.push_back(stoi(levelStr));
        startPos = currPos+1;
    }
    return returnVector;
}

vector<vector<int>> loadReports(const string inputFilePath) {
    ifstream inputFile(inputFilePath);
    string line;
    string num;
    vector<vector<int>> newReport;
    while (std::getline(inputFile, line)) {
        newReport.push_back(getVectorOfNumsFromString(line));
    }
    return newReport;
}

bool checkReport(const vector<int> &report) {
    if (report[0] == report[1]) {
        return false;
    }

    std::function<bool(int a, int b)> evaluator;
    if (report[0] < report[1]) {
        evaluator = [](int a, int b) {
            int difference = abs(a - b);
            return (difference > 0 && difference <= 3) && a < b; 
        };
    } else {
        evaluator = [](int a, int b) { 
            int difference = abs(a - b);
            return (difference > 0 && difference <= 3) && a > b; 
        };
    }

    int numberOfLevels = report.size();
    for (int i=0; i<numberOfLevels -1; i++) {
        if (!(evaluator(report[i], report[i+1]))) {
            return false;
        }
    }
    return true;    
}

int main() {
    vector<vector<int>> reportsVector = loadReports("./success.txt");

    int correctResults = 0;
    for (auto report : reportsVector) {
        if (checkReport(report)) correctResults++;
    }
    cout << correctResults << " safe reports." << endl;
}