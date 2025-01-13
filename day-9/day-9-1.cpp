#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

// 6288707484810

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

    string toString() const {
        ostringstream os;
        if (this->fileId == -1)
            os << ".";
        else
            os << "[" << this->fileId << "]";
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

    string toString() const {
        ostringstream os;
        for (auto b : this->map) {
            os << b.toString();
        }
        os << endl;
        return os.str();
    }

    vector<Block>::iterator getNextFreeSlot() {
        return find_if(this->map.begin(), this->map.end(), [](const Block& b) {return b.isFree();});
    }

    void defrag() {
        for (vector<Block>::reverse_iterator b = this->map.rbegin(); b != this->map.rend(); b++) {
            if (!(*b).isFree()) {
                vector<Block>::iterator nextFreeSlot = getNextFreeSlot();
                
                // if nextFreeSlot position comes after the reverse_iterator (b)
                // then we are de-fragged
                if (nextFreeSlot > --b.base()) {
                    break;
                }
                *nextFreeSlot = *b;
                *b = Block(-1);
            }
        }
    }

    long calculateChecksum() const {
        int mapSize = this->map.size();
        long total = 0;
        for (int i=0; i<mapSize; i++) {
            int fileId = this->map[i].getFileId();
            if (fileId >= 0) {
                total += (i * fileId);
            }
        }
        return total;
    }
};

int main() {
    DiskMap dm;
    dm.loadDiskmap("./input.txt");
    cout << "\n---\nBefore:" << endl;
    cout << dm.toString() << endl;
    dm.defrag();
    cout << "\n---\nAfter:" << endl;    
    cout << dm.toString() << endl;
    cout << "\n---\nChecksum: " << dm.calculateChecksum() << endl;
}

