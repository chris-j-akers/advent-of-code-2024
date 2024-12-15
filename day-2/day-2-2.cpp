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


// Should be 'getEvaluator()'

std::function<bool(int leftLevel, int rightLevel)> getEvaluator(const vector<int> report) {
    
}

bool checkReport(const vector<int> &report) {
    if (report[0] == report[1]) {
        return false;
    }
    // Going to build an evaluation function as a lamda, starting with which
    // comparison to use.
    std::function<bool(int leftLevel, int rightLevel)> levelComparison;
    if (report[0] < report[1]) {
        levelComparison = [](int leftLevel, int rightLevel) { return leftLevel < rightLevel; }; 
    } else {
        levelComparison = [](int leftLevel, int rightLevel) { return leftLevel > rightLevel; }; 
    }

    std::function<bool(int leftLevel, int rightLevel)> levelEvaluator = {
        [&levelComparison](int leftLevel, int rightLevel) { 
            int difference = abs(leftLevel - rightLevel);
            return (difference > 0 && difference <= 3) && levelComparison(leftLevel, rightLevel);
        }
    };

    int numberOfLevels = report.size();
    for (int i=0; i<numberOfLevels -1; i++) {
        if (!(levelEvaluator(report[i], report[i+1]))) {
            // delete and recursive call? (whlle report Length > 1)
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