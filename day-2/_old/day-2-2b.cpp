#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<functional>

using namespace std;

// I think there are 332 safe reports.
// Not 346 (too low)
// Not 373 (doesn't say)
// Not 371 (doesn't say)

bool checkReport(const vector<int> &report);

string reportToString(const vector<int> &report) {
    ostringstream os;
    for (auto level: report) {
        os << level << ' ';
    }
    return os.str();
}

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


/*

- CheckReport fails
- Call Dampner
- Dampner removes first item, then calls checkReport()
- If it fails, it removes the second item, then calls checkreport()
- If it succeeds then it returns true
- If it can't succeed then returns false

*/

/*
Should be a list, then can copy/remove.

*/

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
    const auto lessThan = [](int a, int b) { return a < b; };
    const auto greaterThan = [](int a, int b) { return a > b; };

    int currLevel = 0;
    int failures = 0;

    if (report[0] == report[1] && report[1] == report[2]) {
        cout << "Found a report with the same 3 levels at the beginning, failing this report: " << reportToString(report) << endl;
        return false;
    }

    std::function<bool(int a, int b)> chosenExpression;
    if (report[0] == report[1]) {
        // This is already a failure edge-case so increment the count
        cout << "Found a report with the same 2 levels at the beginning, so dampener will be applied: " << reportToString(report) << endl;
        failures++;
        if (report[0] < report[2]) chosenExpression = lessThan;
        if (report[0] > report[2]) chosenExpression = greaterThan;
        currLevel = 3;
    }    

    // Finally!
    if (report[0] < report[1]) {
        chosenExpression = lessThan;
        currLevel = 2;
    } else {
        chosenExpression = greaterThan;
        currLevel = 2;
    }

    // Now we can build our Lambda for comparing each item
    const auto evaluator = [&chosenExpression](const int l, const int r) {
        int difference = abs(l - r);
        if (!(chosenExpression(l, r) && difference > 0 && difference <= 3)) {
            return false;
        }
        else {
            return true;
        }
    };

    int difference = 0;
    int numberOfLevels = report.size();
    for (int i=0; i<numberOfLevels -1; i++) {
        difference = abs(report[i] - report[i+1]);
        if (!(evaluator(report[i], report[i+1]) && difference > 0 && difference <= 3)) {
            if (!dampener(report)) return false;
        }
    }
    return true;   


vector<vector<int>> loadReports(const string inputFilePath) {
    ifstream inputFile(inputFilePath);
    string line;
    string num;
    vector<vector<int>> newReports;
    while (std::getline(inputFile, line)) {
        newReports.push_back(getVectorOfNumsFromString(line));
    }
    cout << newReports.size() << " reports loaded" << endl;
    return newReports;
}



int main() {
    vector<vector<int>> reportsVector = loadReports("./input.txt");
    
    bool result;
    int correctResults = 0;

    for (auto report : reportsVector) {
        if (report[0] == report[1] == report[3])  {
            result = false;
        }
        else {
            result = checkReport(report);
        }
        if (result) correctResults++;
    }
    cout << "I think there are " << correctResults << " safe reports." << endl;
}




