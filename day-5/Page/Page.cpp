#include "Page.h"

using namespace std;

Page::Page(int number) {
    this->number = number;
}

int Page::getPageNumber() const {
    return number;
}

bool Page::operator>(Page p) {
    if (find(this->before.begin(), this->before.end(), p.getPageNumber()) != this->before.end()) {
        return true;
    }
    return false;
}

bool Page::operator<(Page p) {
    if (find(this->after.begin(), this->after.end(), p.getPageNumber()) != this->after.end()) {
        return true;
    }
    return false;
}

bool Page::operator==(Page p) {
    return this->getPageNumber() == p.getPageNumber();
}

void Page::addPageAfter(Page p) {
    this->after.push_back(p);
}

void Page::addPageBefore(Page p) {
    this->before.push_back(p);
}

// Not that pretty, but useful! Forgot all about the << operator having
// to be overloaded as a 'friend' thing.
ostream& operator<<(ostream& os, const Page &p) {
    os << "======" << endl;
    os << "  " << p.getPageNumber() << endl;

    os << "------" << endl;
    os << "BEFORE" << endl;
    os << "------" << endl;
    for (const auto& page : p.before) {
        os << "  " << page.getPageNumber() << endl;
    }

    os << "-----" << endl;
    os << "AFTER" << endl;
    os << "-----" << endl;
    for (const auto& page : p.after) {
        os << "  " << page.getPageNumber() << endl;
    }
    os << "======" << endl;

    return os;
}
