#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

class Block {
    int fileId;

public:
    Block(int fileId) : fileId(fileId) {}

    int getFileId() const {
        return this->fileId;
    }

    bool isFree() const {
        return this->fileId == -1;
    }

    string toString() {
        ostringstream os;
        if (this->fileId == -1)
            os << ".";
        else
            os << this->fileId;
        return os.str();
    }
};

class DiskMap {
    vector<Block> map;

public:
    void loadDiskmap(const string inputFilePath) {
        ifstream inputFile(inputFilePath);
        string line;
        int id=0;
        getline(inputFile, line);
        int lineLength = line.size();
        for (int i=0; i<lineLength; i++) {
            int blockCount = line[i]-'0';
            for(int blocks=0; blocks<blockCount; blocks++)
                this->map.push_back(Block(id));
            i++;
            int freeBlockCount = line[i]-'0';
            for(int freeBlocks=0; freeBlocks<freeBlockCount; freeBlocks++)
                this->map.push_back(Block(-1));
            id++;
        }
    }

    vector<Block>::iterator getNextFreeSlot() {
        return find_if(this->map.begin(), this->map.end(), [](const Block& b) {return b.isFree();});
    }

    void defrag() {
        auto nextFreeSlot = getNextFreeSlot();
        for (auto b = this->map.rbegin(); b != this->map.rend(); b++) {
            if (!(*b).isFree()) {
                *nextFreeSlot = *b;
                *b = Block(-1);
            }
            nextFreeSlot = getNextFreeSlot();  
            cout << this->toString() << endl;
        }
    }

    string toString() {
        ostringstream os;
        for (auto b : this->map) {
            os << b.toString();
        }
        os << endl;
        return os.str();
    }
};

int main() {
    DiskMap dm;
    dm.loadDiskmap("./example.txt");
    cout << "\n---\nBefore:" << endl;
    cout << dm.toString() << endl;
    dm.defrag();
    cout << "\n---\nAfter:" << endl;    
    cout << dm.toString() << endl;
}

