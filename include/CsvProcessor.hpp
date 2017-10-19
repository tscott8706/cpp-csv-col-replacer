#ifndef CSV_PROCESSOR_H
#define CSV_PROCESSOR_H

#include "CsvArgs.hpp"
#include <string>

class CsvProcessor
{
public:
    CsvProcessor(CsvArgs &args);

    void replaceColValues();

private:
    int findColToReplace(const std::string &headerName);
    void getColHeaders();
    void replaceAllCols(int colNum, std::string replaceVal);
    std::string determineNextColWord(int col, int colNum,
        const std::string &replaceVal, const std::string &word);
    std::string getOutputWordDelimiter(int col);

    CsvArgs &args;
    std::string colHeaders;
    int numCols;
    const int COL_NOT_FOUND;
};

#endif
