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

bool checkReport(const vector<int> &report, const std::function<bool(int a, int b)> eval) {
    int reportLength = report.size();    
    int difference = 0;

    auto evaluator = [&eval](const int l, const int r) {
        int difference = abs(l - r);
        if (!(eval(l, r) && difference > 0 && difference <= 3)) {
            return false;
        }
        else {
            return true;
        }
    };

    int failures = 0;
    for (int i=0; i < reportLength -1; i++) {
        if (!evaluator(report[i], report[i+1])) {
            cout << "FAIL|" << i << "|for [" << reportToString(report) << "]";
            if (++failures > 1) {
                cout << " (Too many FAILS, returning false)" << endl;
                return false;
            }
            if ((i+2 <= reportLength && !evaluator(report[i], report[i+2])) || i+2 >reportLength) {
                cout << " (dampener didn't work, returning false)" << endl;                
                return false;
            }
            cout << " (Applied dampener)" << endl;
            i++;
        }
    }
    cout << "SUCC|for [" << reportToString(report) << "]" << endl;
    return true;
}

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

std::function<bool(int a, int b)> getEvaluator( int first, int second, int third) {
    auto lessThan = [](int a, int b) { return a < b; };
    auto greaterThan = [](int a, int b) { return a > b; };

    if (first == second) {    
        if (second < third) return lessThan;
        if (second > third) return greaterThan;
    }

    if (second < first) {
        return lessThan;
    } else {
        return greaterThan;
    }
}


int main() {
    vector<vector<int>> reportsVector = loadReports("./example.txt");
    
    bool result;
    int correctResults = 0;

    for (auto report : reportsVector) {
        if (report[0] == report[1] == report[3])  {
            result = false;
        }
        else {
            result = checkReport(report, getEvaluator(report[0], report[1], report[2]));
        }
        if (result) correctResults++;
    }
    cout << "I think there are " << correctResults << " safe reports." << endl;
}




