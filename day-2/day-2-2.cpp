#include<iostream>
#include<fstream>
#include<string>
#include<list>
#include<sstream>
#include<functional>

using namespace std;

// I think there are 398 safe reports.

string reportToString(const list<int> &report) {
    ostringstream os;
    for (auto level: report) {
        os << level << ' ';
    }
    return os.str();
}

list<int> extractLevelsFromReportString(const string s) {
    list<int> returnList;    
    int startPos = 0;
    int currPos = 0;
    string levelStr;
    while(currPos < s.size()) {
        currPos = s.find(" ", startPos);
        levelStr = s.substr(startPos, currPos-startPos);        
        returnList.push_back(stoi(levelStr));
        startPos = currPos+1;
    }
    return returnList;
}

vector<list<int>> loadReports(const string inputFilePath) {
    ifstream inputFile(inputFilePath);
    string line;
    vector<list<int>> newReport;
    while (std::getline(inputFile, line)) {
        newReport.push_back(extractLevelsFromReportString(line));
    }
    return newReport;
}

// This helps us with a couple of edge-cases where the first two levels of a 
// report are the same. It means we can't select an evaluator so need to
// fail it directly.
bool firstTwoLevelsTheSame(const list<int> &report) {
    if (report.size() < 2) {
        return false;
    }
    auto iter = report.begin();
    return *iter == *(++iter);
}

// Lets us remove an item from a list at a specific index. This is still more
// efficient than using a vector to delete, so there.
void deleteListItemAt(list<int> &report, int pos) {
    auto iter = report.begin();
    for (int index=0; index != pos; index++) {
        iter++;
    }
    report.erase(iter);
}

// Build a lambda, depending on whether we're increasing or decreasing. A lot of
// code for just one boolean expression!
std::function<bool(int a, int b)> getEvaluator(const list<int> &report) {
    auto iter = report.begin();    
    if (*iter < *(++iter)) {
        return [](int leftLevel, int rightLevel) { 
                    return leftLevel < rightLevel;
        };
    }
    else {
        return [](int leftLevel, int rightLevel) { 
                    return leftLevel > rightLevel;
        };
    }
}

bool checkReport(list<int> &report, std::function<bool(int a, int b)> evaluator) {
    int leftLevel, rightLevel, difference;
    for (auto iter = report.begin(); iter != --report.end(); ++iter) {
      
        // There's some funky iterator stuff, here I got in trouble with.
        //
        // When passing iterator values as params they will be de-referenced and 
        // evaluated in the same statement, so I can't do: 
        //
        // evaluator(*iter, *(++iter).
        // 
        // ^^^ This = race-condition and ends up passing the same value for each 
        // parameter.
        //
        // I can do this above, in the boolean comparision expression because 
        // the left is evaluated before the right in sequence.

        leftLevel = *iter;
        rightLevel = *(++iter);        
        difference = abs(leftLevel - rightLevel);

        if (!(difference > 0 && difference <= 3) || !evaluator(leftLevel, rightLevel)) {        
            return false;
        }
        else {
            --iter;
        }
    }
    return true;   
}

// Bit brute-forcey. We just have to try removing a level from the report and
// re-testing one at a time. This is tricky because it's a list, but still better
// than using a vector when we're removing items.
bool applyDampener(const list<int> &report) {
    list<int> reportCopy = report;    
    int reportLength = report.size();
    for(int level=0; level < reportLength; level++) {
        
        deleteListItemAt(reportCopy, level);
        
        // Edgecase failure. Bastard.
        if (firstTwoLevelsTheSame(reportCopy)) {
            reportCopy = report;
            continue;
        }
        
        if (checkReport(reportCopy, getEvaluator(reportCopy))) {
            return true;
        }
        else {
            reportCopy = report;
        }
    }

    return false;
}

int main() {
    vector<list<int>> reportsList = loadReports("./input.txt");

    int correctReports = 0;
    int failedReports = 0;

    for (auto report : reportsList) {
        if ((!firstTwoLevelsTheSame(report)) && checkReport(report, getEvaluator(report))) {
            correctReports++;
        } 
        else {
            if (applyDampener(report)) {
                correctReports++;
            }
            else {
                failedReports++;
            }
        }
    }
    cout << correctReports << " safe reports." << endl;
}