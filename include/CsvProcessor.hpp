#ifndef CSV_PROCESSOR_H
#define CSV_PROCESSOR_H

#include "CsvArgHandler.hpp"
#include <istream>
#include <string>

class CsvProcessor
{
public:
    CsvProcessor(CsvArgs &args);
    ~CsvProcessor();

    bool replaceColValues();

protected:
    std::string getNextLineFromInputFile();
    void writeNextLineToOutputFile();

private:
    int findColNum(std::string headerName);
    bool getColHeaders();
    bool replaceAllCols(int colNum, std::string replaceVal);

    CsvArgs &args;
    std::string colHeaders;
    int numCols;
};

#endif
