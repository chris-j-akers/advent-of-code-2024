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

vector<Multi> extractMultis(const string text) {
    regex multiRegex("(mul\\(\\d{1,3},\\d{1,3}\\))|do\\(\\)|don\\'t\\(\\)");
    bool recordOn = true;
    vector<Multi> returnVector;

    for (std::sregex_iterator i = sregex_iterator(text.begin(), text.end(), multiRegex); i != sregex_iterator(); ++i) {
        smatch instruction = *i;

        if (instruction.str() == "don't()") {
            recordOn = false;
        }
        if (instruction.str() == "do()") {
            recordOn = true;
        }
        if (instruction.str().substr(0,3) == "mul" && recordOn) {
            returnVector.push_back(Multi(instruction.str()));
        }
    }
    return returnVector;
}

string loadInput(const string inputFilePath) {
    ifstream inputFile(inputFilePath);
    stringstream buffer;
    buffer << inputFile.rdbuf();
    return buffer.str();    
}

int main()  {
    string fileContents = loadInput("./input.txt");
    vector<Multi> multis = extractMultis(fileContents);
    for ( auto multi : multis) {
        cout << multi.toString() << endl;
    }
    cout << "\nsum: " << sumAllMultis(multis) << endl;
}