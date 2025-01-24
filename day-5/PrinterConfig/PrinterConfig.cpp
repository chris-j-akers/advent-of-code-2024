#include "PrinterConfig.h"

using namespace std;

// public

Page PrinterConfig::lookupPage(const int i) {
    Page p = *(find_if(this->pageConfig.cbegin(), this->pageConfig.cend(), [i](const Page p) {return p.getPageNumber() == i; }));
    return p;
}

void PrinterConfig::ImportConfiguration(const string inputFilePath) {
    ifstream inputFile(inputFilePath);
    string line;

    // Load Page Order Configuration
    while (getline(inputFile, line) && !line.empty()) {
        pair<Page, Page> beforeAndAfterPages = getBeforeAndAfterPages(line);
        upsertConfig(beforeAndAfterPages.first, beforeAndAfterPages.second);
    }
}

string PrinterConfig::toString() {
    ostringstream os;
     for(auto p: this->pageConfig) {
        os << p;
        os << endl;
    }
    os << endl;
    return os.str();
}

// private

void PrinterConfig::upsertConfig(Page before, Page after) {
    // if first (before) doesn't exist in pages, add it then add second to the after
    auto p = find(pageConfig.begin(), pageConfig.end(), before);
    if (p == pageConfig.end()) {
        before.addPageAfter(after);
        pageConfig.push_back(before);
    }
    else {
        (*p).addPageAfter(after);
    }
    // if second (after) doesn't exist in pages, add it then add first to the before
    p = find(pageConfig.begin(), pageConfig.end(), after);
    if (p ==pageConfig.end()) {
        after.addPageBefore(before);
        pageConfig.push_back(after);
    }
    else {
        (*p).addPageBefore(before);
    }
}

pair<Page, Page> PrinterConfig::getBeforeAndAfterPages(const string s) {
    int cursor = 0;
    cursor = s.find("|", 0);
    return make_pair(Page(stoi(s.substr(0, cursor))), Page(stoi(s.substr(cursor+1, s.length()))));
}




