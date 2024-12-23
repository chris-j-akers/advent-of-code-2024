#include<list>
#include<fstream>
#include<algorithm>

#include "../Page/Page.h"

class PrinterConfig {
    private:
        list<Page> pageConfig;

        pair<Page, Page> getBeforeAndAfterPages(const string s);
        void upsertConfig(Page before, Page after);

    public:
        void ImportConfiguration(const string inputFilePath);
        void loadPrintJob(const string inputFilePath);
        Page lookupPage(const int i);
        void printManual();
        string toString();
};