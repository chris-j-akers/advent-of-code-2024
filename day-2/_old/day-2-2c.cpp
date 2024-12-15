#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<functional>

using namespace std;

// I think there are 332 safe reports.

bool checkReport(const vector<int> &report);

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

bool dampener(const vector<int> &report) {
    const int reportLength = report.size();
    vector<int> reportCopy;
    for (int i=0; i<reportLength; i++) {
        reportCopy = report;
        reportCopy.erase(reportCopy.begin() + i);
        if (checkReport(reportCopy)) {
            return true;
        }
    }
    return false;
}

bool checkReport(const vector<int> &report) {
    std::function<bool(int a, int b)> eval;
    if (report[0] < report[1]) {
        eval = [](int a, int b) { return a < b; };
    } 
    else {
        eval = [](int a, int b) { return a > b; };
    }    
    int numberOfLevels = report.size();    
    int difference = 0;
    for (int i=0; i<numberOfLevels -1; i++) {
        difference = abs(report[i] - report[i+1]);
        if (!(eval(report[i], report[i+1]) && difference > 0 && difference <= 3)) {
            if (!dampener(report)) return false;
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
        result = checkReport(report);
        if (result) correctResults++;
    }
    cout << "I think there are " << correctResults << " safe reports." << endl;
}