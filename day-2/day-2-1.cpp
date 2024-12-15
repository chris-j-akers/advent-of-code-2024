#include<iostream>
#include<fstream>
#include<string>
#include<list>
#include<sstream>
#include<functional>

using namespace std;

// I think there are 332 safe reports.

string reportToString(const list<int> &report) {
    ostringstream os;
    for (auto level: report) {
        os << level << ' ';
    }
    return os.str();
}


list<int> getListOfLevelsFromString(const string s) {
    list<int> levels;    
    int stringStartPos = 0;
    int stringCurrPos = 0;
    string levelStr;
    while(stringCurrPos < s.size()) {
        stringCurrPos = s.find(" ", stringStartPos);
        levelStr = s.substr(stringStartPos, stringCurrPos-stringStartPos);        
        levels.push_back(stoi(levelStr));
        stringStartPos = stringCurrPos+1;
    }
    return levels;
}


// while (list1Iterator != list1.end() && list2Iterator != list2.end()) {

bool checkReport(const list<int> &report, const std::function<bool(int a, int b)> eval) {
    int numberOfLevels = report.size();    
    int difference = 0;
    for (auto reportsIter = report.begin(); reportsIter -1; i++) {
        difference = abs(report[i] - report[i+1]);
        if (!(eval(report[i], report[i+1]) && difference > 0 && difference <= 3)) {
            return false;
        }
    }
    return true;    
}

vector<list<int>> loadReports(const string inputFilePath) {
    ifstream inputFile(inputFilePath);
    string line;
    string num;
    vector<list<int>> newReport;
    while (std::getline(inputFile, line)) {
        newReport.push_back(getListOfLevelsFromString(line));
    }
    return newReport;
}


int main() {
    vector<list<int>> reportsList = loadReports("./input.txt");
    
    for (list<int> l : reportsList) {
        cout << "got list: " << reportToString(l) << endl;
    }

    // bool result;
    // int correctResults = 0;

    // for (auto report : reportsVector) {
    //     if (report[0] < report[1]) {
    //         result = checkReport(report, [](int a, int b) { return a < b; });
    //     } 
    //     else {
    //         result = checkReport(report, [](int a, int b) { return a > b; });
    //     }
    //     if (result) correctResults++;
    // }
    // cout << "I think there are " << correctResults << " safe reports." << endl;
}