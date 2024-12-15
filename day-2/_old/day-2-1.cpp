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

bool checkReport(const vector<int> &report, const std::function<bool(int a, int b)> eval) {
    int numberOfLevels = report.size();    
    int difference = 0;
    for (int i=0; i<numberOfLevels -1; i++) {
        difference = abs(report[i] - report[i+1]);
        if (!(eval(report[i], report[i+1]) && difference > 0 && difference <= 3)) {
            return false;
        }
    }
    return true;    
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


int main() {
    vector<vector<int>> reportsVector = loadReports("./success.txt");
    
    bool result;
    int correctResults = 0;

    for (auto report : reportsVector) {
        if (report[0] < report[1]) {
            result = checkReport(report, [](int a, int b) { return a < b; });
        } 
        else {
            result = checkReport(report, [](int a, int b) { return a > b; });
        }
        if (result) correctResults++;
    }
    cout << "I think there are " << correctResults << " safe reports." << endl;
}