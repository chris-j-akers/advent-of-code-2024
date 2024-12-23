#include "Printer.h"

Printer::Printer(const string configFilePath) {
    this->configFile = configFilePath;
}

void Printer::loadPrintJob() {
    ifstream inputFile(this->configFile);
    string line;

    // Skip ahead
    while (getline(inputFile, line) && !line.empty());

    // Load print orders
    vector<vector<int>> printConfig;
    while (getline(inputFile, line) && !line.empty()) {
        this->printJob.push_back(getVectorOfNumsFromString(line));
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

void Printer::loadConfig() {
    this->config.ImportConfiguration(this->configFile);
}

void Printer::printConfig() {
    cout << this->config.toString() << endl;
}