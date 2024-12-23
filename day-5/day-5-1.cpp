#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<list>
#include<sstream>
#include<functional>
#include "Printer/Printer.h"

// I'm taking a gamble on part II. My expectation is that we'll be asked to 
// fix the pager-ordering for the broken ones so have written this with that in
// mind. Watch this space.

// EDIT: Maybe a bit overboard on this one with the OO? I'm not sure, but it
// fits together nicely.

using namespace std;

int main() {
    Printer p("./input.txt");
    p.loadConfig();
    p.loadPrintJobs();

    vector<vector<int>> workingJobs = p.getCorrectJobs();
    for (auto j: workingJobs) {
        cout << ": ";
        for (auto page : j) {
            cout << page << ",";
        }
        cout << endl;
    }
    cout << "Number of working jobs: " << workingJobs.size() << endl;

    int total = 0;
    for( auto j: workingJobs) {
        total += j[j.size()/2];
    }
    cout << "Total: " << total << endl;
}