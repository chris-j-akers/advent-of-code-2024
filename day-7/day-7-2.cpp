#include<iostream>
#include<sstream>
#include<fstream>
#include<queue>
#include<utility>
#include<vector>

using namespace std;

// Recursion question 'innit. Yep, I used a Queue, when could have used a vector
// or even an array, but, again, not much data and I like using the STL interfaces.
// The fact that you can shrink the queue as you recurse is nice to me, especially
// when we're not really dealing with much to copy in terms of params. If there
// where thousands or millions of values then maybe moving along an array would
// be better.

// Total is: 32292731 <- Too low, but the numbers aren't being parsed properly
// as I can see some negative ones that don't exist in the file.

// Issue was int vs long, but still: 16752228564 is too low, apparently.

// Changed all required to long and finally: 850435817339 is the right answer.

// Part 2: Lol 5817338842265 is too low! :o
// It's the old left-to-right precedence. This is right: 104824810233437

string queueToString(const queue<int> &q) {
    ostringstream os;
    queue<int> q2 = q;
    os << "{";
    while (q2.size() >0) {
        os << q2.front() << ",";
        q2.pop();
    }
    os.str().pop_back();
    string s = os.str();
    // Lol, finally cleaning these up by removing the last comma ;)
    s.pop_back();
    s.push_back('}');
    return s;
}

struct Equation {
    queue<int> vals;
    long result;

    Equation() {}
    Equation(queue<int> vals, long result) : vals(vals), result(result) {}

    long sumVals() const {
        queue<int> q = this->vals;
        long total = 0;
        while (!q.empty()) {
            total += q.front();
            q.pop();
        }
        return total;
    }

    string toString() const {
        ostringstream os;
        os << "Expected Result: " << this->result << ", Available Values: " << queueToString(this->vals);
        return os.str();
    }

};

vector<Equation> typedef Equations;

queue<int> getEquationVals(const string s) {
    queue<int> vals;
    int startPos =0;
    int currPos = 1;
    string valStr;
    while(currPos < s.size()) {
        currPos = s.find(" ", startPos);
        valStr = s.substr(startPos, currPos-startPos);
        vals.push(stoi(valStr));
        startPos = currPos+1;
    }
    return vals;
}

Equations loadEquations(const string inputFilePath) {
    ifstream inputFile(inputFilePath);
    string line;
    long result;
    Equations eqs;
    while (getline(inputFile, line, ':')) {
        result = stoll(line);
        getline(inputFile, line);
        eqs.push_back(Equation(getEquationVals(line.erase(0,1)), result));
    }
    return eqs;
}

// I'm not going to overload || operator, here, just pretend it's a token
// that's been assigned an expression :shrug:
long concat(long l1, long l2) {
    string l1Str = to_string(l1);
    string l2Str = to_string(l2);

    //cout << "RET: " << l1Str + l2Str << endl;
    return stoll(l1Str + l2Str);
}

bool calculate(queue<int> eqs, const long target, const long currentTotal) {
    if (eqs.size() == 0) {
        return currentTotal == target;
    }

    int head = eqs.front();
    eqs.pop();

    // Actually, I did struggle a bit on this part as I'm used to single recursive answers, not
    // choosing between two. It clicked but only after a little bit of faffing.
    if (calculate(eqs, target, head + currentTotal) || calculate(eqs, target, head * currentTotal) || calculate(eqs, target, concat(currentTotal, head))) {
        return true;
    }

    return false;
}

int main() {
    Equations eqs = loadEquations("./input.txt");
    long total = 0;
    for (Equation eq : eqs) {
        cout << eq.toString() << " ";
        if (calculate(eq.vals, eq.result, 0)) {
            cout << "(Working Equation)" << endl;
            total += eq.result;
        }
        else {
            cout << "(Non-Working equation)" << endl;
        }
    }
    cout << "---" << endl << "Total is: " << total << endl;
}

