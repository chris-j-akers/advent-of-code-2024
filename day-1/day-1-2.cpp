#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<list>

// Total distance is: 1830467

using namespace std; 

void load_lists(const string inputFilePath, list<int> &list1, list<int> &list2) {
    ifstream inputFile(inputFilePath);
    string line; 

    while (std::getline(inputFile, line)) {
        size_t splitPos = line.find(" ");
        list1.push_back(std::stoi(line.substr(0, splitPos)));
        list2.push_back(std::stoi(line.substr(splitPos+3))); 
    }

    list1.sort();
    list2.sort();
}

long total_distance(const list<int> &list1, const list<int> &list2) {
    int difference = 0;
    auto list1Iterator = list1.cbegin();
    auto list2Iterator = list2.cbegin();
    int count = 0;

    while (list1Iterator != list1.cend() && list2Iterator != list2.cend()) {
        difference += abs(*list2Iterator - *list1Iterator);
        list1Iterator++;
        list2Iterator++;
        count++;
    }
    
    return difference;
}

int main() {
    std::list<int> list1;
    std::list<int> list2;

    // Loads and sorts the lists
    load_lists("./input.txt", list1, list2);
    long distance = total_distance(list1, list2);
    cout << "Total distance is: " << distance << endl;

    int similarityScore = 0;
    for (auto l1 : list1) {
        similarityScore += l1 * count(list2.cbegin(), list2.cend(), l1);
    }
    cout << "Similarity score is: " << similarityScore << endl;

}