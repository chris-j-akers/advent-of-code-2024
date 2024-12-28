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

void printJobInfo(Printer p) {
    cout << "WORKING JOBS" << endl;
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

int main() {

    // This is a bit of a casserole of nonsense, but I have to move on!

    // I assumed that we would be asked to resort the jobs, but not to get some
    // weird value from the middle of the printer jobs array, though that makes 
    // sense to stop me faking the answer,  So, I have to 
    // create the first printer, get all the incorrect jobs and load them into
    // a second printer, then run the re-order and get the total. Such a pain,
    // but if I refactored everything now it would take all day and, besides, 
    // which, my way makes more sense because in a real domain people would 
    // just want working print jobs not some weird total number.

    string inputFile = "./input.txt";

    Printer p(inputFile);
    p.loadConfig();
    p.loadPrintJobs();
    printJobInfo(p);

    cout << endl;
    cout << endl;

    Printer p2(inputFile);
    p2.loadConfig();
    p2.loadPrintJobs(p.getInCorrectJobs());
    printJobInfo(p2);
    p2.reorderJobs();
    printJobInfo(p2);
}