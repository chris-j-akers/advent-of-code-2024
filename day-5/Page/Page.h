#pragma once
#include<algorithm>
#include<vector>
#include<ostream>
#include<sstream>

using namespace std;

class Page {
    int number;
    vector<Page> before;
    vector<Page> after;

public:
    Page(int pageNumber);
    int getPageNumber() const;
    void addPageBefore(Page p);
    void addPageAfter(Page p);
    bool isAfter(int pageNumber) const;
    bool isBefore(int pageNumber) const;
    bool isPageNumber(int pageNumber) const;
    bool operator==(Page p);
    friend ostream& operator<<(ostream& os, const Page &p);
};
