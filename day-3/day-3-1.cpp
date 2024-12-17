#include<string>
#include<iostream>
#include<sstream>
#include<ostream>
#include<vector>
#include<fstream>
#include<regex>

using namespace std;

struct Multi {
    int left;
    int right;

    int calc() {
        return left * right;
    }

    Multi(string multiStr) {
        regex digitsRegex("(\\d{1,3})");
        std::sregex_iterator i = sregex_iterator(multiStr.begin(), multiStr.end(), digitsRegex);
        left = stoi((*i).str() );
        right = stoi((*++i).str());
    }

    string toString() {
        ostringstream os;
        os << "(" << left << "," << right << ")" << " = " << calc();
        return os.str();
    }
};

long sumAllMultis(vector<Multi> multis) {
    long total = 0;
    for (auto multi : multis) {
        total += multi.calc();
    }
    return total;
}

string loadInput(const string inputFilePath) {
    ifstream inputFile(inputFilePath);
    stringstream buffer;
    buffer << inputFile.rdbuf();
    return buffer.str();    
}

vector<Multi> extractMultis(const string text) {
    regex multiRegex("mul\\(\\d{1,3},\\d{1,3}\\)");

    vector<Multi> returnVector;
    for (std::sregex_iterator i = sregex_iterator(text.begin(), text.end(), multiRegex); i != sregex_iterator(); ++i) {
        smatch multi = *i;
        returnVector.push_back(Multi(multi.str()));
    }
    return returnVector;
}

int main()  {
    string fileContents = loadInput("./input.txt");
    vector<Multi> multis = extractMultis(fileContents);
    for ( auto multi : multis) {
        cout << multi.toString() << endl;
    }
    cout << "\nsum: " << sumAllMultis(multis) << endl;
}