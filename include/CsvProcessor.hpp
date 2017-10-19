#ifndef CSV_PROCESSOR_H
#define CSV_PROCESSOR_H

#include <istream>
#include <string>

class CsvProcessor
{
public:
    CsvProcessor(std::istream &inputData);

    std::string replaceColVals(const std::string &colToOverwrite,
        const std::string &replaceVal);

private:
    int findColToReplace(const std::string &headerName);
    void getColHeaders();
    std::string replaceAllCols(int colNum, const std::string &replaceVal);
    void checkedGetNextWord(std::string &word,
        std::istringstream &colProcessor, const std::string &line,
        bool expectedResult);
    std::string determineNextColWord(int col, int colNum,
        const std::string &replaceVal, const std::string &word);
    std::string getOutputWordDelimiter(int col);

    std::istream &inputData;
    std::string colHeaders;
    int numCols;
    const int COL_NOT_FOUND;
};

#endif
