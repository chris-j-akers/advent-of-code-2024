#include "Printer.h"

Printer::Printer(const string configFilePath) {
    this->configFile = configFilePath;
}

void Printer::loadPrintJobs() {
    ifstream inputFile(this->configFile);
    string line;

    // Skip ahead
    while (getline(inputFile, line) && !line.empty());

    // Load print orders
    vector<vector<int>> printConfig;
    while (getline(inputFile, line) && !line.empty()) {
        this->printJobs.push_back(getVectorOfNumsFromString(line));
    }
}

void Printer::loadPrintJobs(vector<vector<int>> jobs) {
    this->printJobs = jobs;
}

void Printer::loadConfig() {
    this->config.ImportConfiguration(this->configFile);
}

void Printer::printConfig() {
    cout << "PRINTER CONFIGURATION" << endl;
    cout << "---------------------" << endl;
    cout << this->config.toString() << endl;
    cout << "JOB LIST" << endl;
    cout << "--------" << endl;
    for(auto j: this->printJobs) {
        for (auto k: j) {
            cout << k << ",";
        }
        cout << endl;
    }
    cout << endl;
}

bool Printer::checkJob(vector<int> job) {
    for (int i=0; i<job.size()-1; i++) {
        Page p = this->config.lookupPage(job[i]);
        if (!p.isBefore(job[i+1])) {
            return false;
        }
    }
    return true;
}

vector<vector<int>> Printer::getCorrectJobs() {
    vector<vector<int>> returnVector;
    for (auto job : this->printJobs) {
        if (checkJob(job)) {
            returnVector.push_back(job);
        }        
    }
    return returnVector;
}

vector<vector<int>> Printer::getInCorrectJobs() {
    vector<vector<int>> returnVector;
    for (auto job : this->printJobs) {
        if (!checkJob(job)) {
            returnVector.push_back(job);
        }        
    }
    return returnVector;
}

void Printer::reorderJobs() {
    // We've set this up so we can just bubble sort them all, now.
    vector<vector<int>> correctedJobs;
    bool swapped;
    for (auto &job : this->printJobs) {
        do {
            swapped = false;
            for (int i=0; i<job.size()-1; i++) {
                Page p = this->config.lookupPage(job[i]);
                if (!p.isBefore(job[i+1])) {
                    int temp = job[i];
                    job[i] = job[i+1];
                    job[i+1] = temp;
                    swapped=true;
                }
            }
        } while(swapped==true);
    }
}

vector<int> Printer::getVectorOfNumsFromString(const string s) {
    vector<int> returnVector;    
    int startPos = 0;
    int currPos = 0;
    string levelStr;
    while(currPos < s.size()) {
        currPos = s.find(",", startPos);
        levelStr = s.substr(startPos, currPos-startPos);
        returnVector.push_back(stoi(levelStr));
        startPos = currPos+1;
    }
    return returnVector;
}