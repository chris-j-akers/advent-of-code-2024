#include<iostream>
#include "../PrinterConfig/PrinterConfig.h"

class Printer {
    string configFile;
    PrinterConfig config;
    vector<vector<int>> printJobs;

    vector<int> getVectorOfNumsFromString(const string s);

public:
    Printer(const string configFilePath);
    void loadPrintJobs();
    void loadConfig();
    void printConfig();
    
};