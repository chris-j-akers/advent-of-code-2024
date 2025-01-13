#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<list>
#include<algorithm>

using namespace std;

class Block {
    protected:
        int size;

    public:
        Block(int size) : size(size) {}
        virtual ~Block() = default;
        virtual string toString() const = 0;

        int getSize() const { 
            return this->size;
        }
};

class FreeBlock : public Block {
    public:
        FreeBlock(int size) : Block(size) {}

        string toString() const override {
            ostringstream os;
            for (int i=0; i<this->size; i++)
                os << ".";
            return os.str();
        }    
};

class FileBlock : public Block {
    int fileId;

    public:
        FileBlock(int fileId, int size) : fileId(fileId), Block(size) {}

        int getFileId() const {
            return this->fileId;
        }

        string toString() const override {
            ostringstream os;

            for (int i=0; i<this->size; i++)
                os << this->fileId;
            return os.str();
        }
};

class DiskMap {
    list<Block*> map;

    public:
        void loadDiskmap(const string inputFilePath) {
            ifstream inputFile(inputFilePath);
            string line;
            int id=0;
            getline(inputFile, line);
            int lineLength = line.size();
            for (int i=0; i<lineLength; i+=2) {
                int blockCount = line[i]-'0';
                this->map.push_back(new FileBlock(id, line[i]-'0'));
                if (i+1 >= lineLength)
                    // This is actually the last item on the line
                    break;
                this->map.push_back(new FreeBlock(line[i+1]-'0'));
                id++;
            }
        }

        string toString() const {
            ostringstream os;
            for (auto b : this->map) {
                os << b->toString();
            }
            os << endl;
            return os.str();
        }

        bool isFree(Block* b) const {
            return typeid(*b) == typeid(FreeBlock);
        }

        list<Block*>::iterator getNextFreeBlock(int size) {
            return find_if(this->map.begin(), this->map.end(), [&size](Block* b) { 
                if (typeid(*b) == typeid(FreeBlock) && b->getSize() >= size)
                    return true;
                else
                    return false;
                });
        }

        void defrag() {
            for (list<Block*>::reverse_iterator reverseIter = this->map.rbegin(); reverseIter != this->map.rend(); ++reverseIter) { 

                if (typeid(*(*reverseIter)) == typeid(FreeBlock))
                    continue;

                list<Block*>::iterator nextFreeBlockIter = this->getNextFreeBlock((*reverseIter)->getSize());
                
                if (nextFreeBlockIter == this->map.end())
                    continue;

                if (distance(this->map.begin(), nextFreeBlockIter) >= distance(this->map.begin(), --reverseIter.base()))
                    continue;

                // Start swapping things around
                FileBlock* fileBlock = dynamic_cast<FileBlock*>(*reverseIter);
                FreeBlock* freeBlock = dynamic_cast<FreeBlock*>(*nextFreeBlockIter);

                int difference = freeBlock->getSize() - fileBlock->getSize();
                
                (*nextFreeBlockIter) = fileBlock;
                
                if (difference > 0) {
                    // So this isn't great because we end up with FreeBlocks next to each
                    // other which will at some point need to be defragged themselves!
                    // But good enough to answer this question and move on!
                    this->map.insert(++nextFreeBlockIter, new FreeBlock(difference));
                }
                (*reverseIter) = new FreeBlock(fileBlock->getSize());
            }
        }

        long calculateChecksum() const {
            // As before, the way we insert the fileblocks means we will be 
            // left with FreeBlocks next to each other which will also need
            // defragging. This is easy to get around in the calculation.
            // Maybe another freespace merge function could be written in the
            // future :shrug:
            int position = 0;
            long total = 0;
            for (Block* block : this->map) {
                for (int i=0; i<block->getSize(); i++) {
                    if (typeid(*block) == typeid(FileBlock))
                        total += position * ((FileBlock*)block)->getFileId();
                    position++;
                }
            }
            return total;
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
    cout << "\n---\nChecksum: " << dm.calculateChecksum() << endl;
}

