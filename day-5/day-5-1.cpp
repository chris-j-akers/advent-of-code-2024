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

void upsertPagesToList(list<Page> &pages, Page before, Page after) {
    // if first (before) doesn't exist in pages, add it then add second to the after
    auto p = find(pages.begin(), pages.end(), before);
    if (p == pages.end()) {
        before.addPageAfter(after);
        pages.push_back(before);
    }
    else {
        (*p).addPageAfter(after);
    }
    // if second (after) doesn't exist in pages, add it then add first to the before
    p = find(pages.begin(), pages.end(), after);
    if (p ==pages.end()) {
        after.addPageBefore(before);
        pages.push_back(after);
    }
    else {
        (*p).addPageBefore(before);
    }

}

list<Page> loadPages(const string inputFilePath) {
    list<Page> pages;
    ifstream inputFile(inputFilePath);
    string line;

    while (std::getline(inputFile, line) && !line.empty()) {
        pair<Page, Page> beforeAndAfterPages = getBeforeAndAfterPages(line);
        cout << "[" << beforeAndAfterPages.first.getPageNumber() << " " << beforeAndAfterPages.second.getPageNumber() << "]" << endl;
        upsertPagesToList(pages, beforeAndAfterPages.first, beforeAndAfterPages.second);
    }
    
    return pages;
}

int main() {
    list<Page> pages = loadPages("./example.txt");
    for( auto p : pages) {
        cout << p << endl;
    }
}