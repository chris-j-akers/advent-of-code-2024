#include<iostream>
#include "../PrinterConfig/PrinterConfig.h"

class Printer {
    string configFile;
    PrinterConfig config;
    vector<vector<int>> printJobs;
    vector<int> correctedJobs;
    vector<int> getVectorOfNumsFromString(const string s);

public:
    Printer(const string configFilePath);
    void loadPrintJobs();
    void loadPrintJobs(vector<vector<int>> jobs);
    void loadConfig();
    void printConfig();
    vector<vector<int>> getCorrectJobs();
    vector<vector<int>> getInCorrectJobs();
    bool checkJob(vector<int> job);
    void reorderJobs() ;
};