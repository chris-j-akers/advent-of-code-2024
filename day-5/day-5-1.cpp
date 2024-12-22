#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<list>
#include<sstream>
#include<functional>
#include "Page/Page.h"

// I'm taking a gamble on part II. My expectation is that we'll be asked to 
// fix the pager-ordering for the broken ones so have written this with that in
// mind. Watch this space.

using namespace std;

pair<Page, Page> getBeforeAndAfterPages(const string s) {
    int cursor = 0;
    cursor = s.find("|", 0);
    return make_pair(Page(stoi(s.substr(0, cursor))), Page(stoi(s.substr(cursor+1, s.length()))));
}

void upsertPageToList(list<Page> pages, Page p) {


}

list<Page> loadPages(const string inputFilePath) {
    list<Page> pages;
    ifstream inputFile(inputFilePath);
    string line;

    while (std::getline(inputFile, line) && !line.empty()) {
        pair<Page, Page> ba = getBeforeAndAfterPages(line);
        cout << "[" << ba.first.getPageNumber() << " " << ba.second.getPageNumber() << "]" << endl;

        // if first (before) doesn't exist in pages, add it then add second to the after
        auto p = find(pages.begin(), pages.end(), ba.first);
        if (p == pages.end()) {
            ba.first.addPageAfter(ba.second);
            pages.push_back(ba.first);
        }
        else {
            (*p).addPageAfter(ba.second);
        }
        // if second (after) doesn't exist in pages, add it then add first to the before
        p = find(pages.begin(), pages.end(), ba.second);
        if (p ==pages.end()) {
            ba.second.addPageBefore(ba.first);
            pages.push_back(ba.second);
        }
        else {
            (*p).addPageBefore(ba.first);
        }
    }
    return pages;
}

int main() {
    list<Page> pages = loadPages("./example.txt");
    for( auto p : pages) {
        cout << p << endl;
    }
}