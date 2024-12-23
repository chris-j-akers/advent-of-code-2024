#include<iostream>
#include "../PrinterConfig/PrinterConfig.h"

class Printer {
    string configFile;
    PrinterConfig config;
    vector<vector<int>> printJob;

    vector<int> getVectorOfNumsFromString(const string s);

public:
    Printer(const string configFilePath);
    void loadPrintJob();
    void loadConfig();
    void printConfig();
};