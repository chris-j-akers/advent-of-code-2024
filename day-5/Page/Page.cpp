#include "Page.h"

using namespace std;

Page::Page(int number) {
    this->number = number;
}

int Page::getPageNumber() const {
    return number;
}

bool Page::isAfter(int pageNumber) const {
    if (find_if(this->before.cbegin(), this->before.cend(), [pageNumber](const Page& page) { return page.getPageNumber() == pageNumber; }) != this->before.cend()) {
        return true;
    }
    return false;
}

bool Page::isBefore(int pageNumber) const {
    if (find_if(this->after.cbegin(), this->after.cend(), [pageNumber](const Page& page) { return page.getPageNumber() == pageNumber; }) != this->after.cend()) {
        return true;
    }
    return false;
}

bool Page::isPageNumber(int pageNumber) const {
    return this->getPageNumber() == pageNumber;
}

void Page::addPageAfter(Page p) {
    this->after.push_back(p);
}

void Page::addPageBefore(Page p) {
    this->before.push_back(p);
}

bool Page::operator==(Page p) {
    return this->getPageNumber() == p.getPageNumber();
}

// Not that pretty, but useful! Forgot all about the << operator having
// to be overloaded as a 'friend' thing.
ostream& operator<<(ostream& os, const Page &p) {

    os << "[" << p.getPageNumber() << "]";

    os << "\tBEFORE [";
    for (const auto& page : p.before) {
        os << page.getPageNumber() << " ";
    }
    os << "]";
    os << "\tAFTER [";
    for (const auto& page : p.after) {
        os << page.getPageNumber() << " ";
    }
    os << "]";
    return os;
}
