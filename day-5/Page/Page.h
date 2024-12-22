#pragma once
#include<algorithm>
#include<vector>
#include<ostream>

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
    bool operator>(Page p);
    bool operator<(Page p);
    bool operator==(Page p);
    friend ostream& operator<<(ostream& os, const Page &p);
};
