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

using namespace std;



int main() {
    Printer p("./example.txt");
    p.loadConfig();
    p.printConfig();
}