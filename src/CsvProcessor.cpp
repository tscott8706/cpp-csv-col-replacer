#include "CsvArgs.hpp"
#include "CsvProcessor.hpp"
#include <sstream>
#include <stdexcept>

CsvProcessor::CsvProcessor(std::istream &inputData):
    inputData(inputData), numCols(0), COL_NOT_FOUND(-1)
{
}

std::string CsvProcessor::replaceColVals(const std::string &colToOverwrite,
    const std::string &replaceVal)
{
    int colNum = findColToReplace(colToOverwrite);
    return colHeaders + "\n" + replaceAllCols(colNum, replaceVal);
}

int CsvProcessor::findColToReplace(const std::string &headerName)
{
    getColHeaders();

    int colNum = COL_NOT_FOUND;
    std::istringstream colHeaderProcessor(colHeaders);
    std::string colHeader;

    while (getline(colHeaderProcessor, colHeader, ','))
    {
        if (colHeader == headerName)
        {
            colNum = numCols;
        }
        numCols++;
    }

    if (colNum == COL_NOT_FOUND)
    {
        throw std::invalid_argument("column name doesn't exist in the input "
            "data\n");
    }

    return colNum;
}

void CsvProcessor::getColHeaders()
{
    if (!getline(inputData, colHeaders))
    {
        throw std::invalid_argument("input data missing\n");
    }
}

std::string CsvProcessor::replaceAllCols(int colNum,
    const std::string &replaceVal)
{
    std::string line;
    std::string word;
    std::string output;

    while (getline(inputData, line))
    {
        std::istringstream colProcessor(line);
        for (int col = 0; col < numCols; col++)
        {
            checkedGetNextWord(word, colProcessor, line, (col != numCols - 1));
            output += (determineNextColWord(col, colNum, replaceVal, word) +
                getOutputWordDelimiter(col));
        }
    }

    return output;
}

void CsvProcessor::checkedGetNextWord(std::string &word,
    std::istringstream &colProcessor, const std::string &line,
    bool expectedResult)
{
    bool result = !getline(colProcessor, word, ',').eof();
    if (result != expectedResult)
    {
        throw std::invalid_argument("Input file is malformed.  " +
            line + " has a different number of columns.  word is " + word);
    }
}

std::string CsvProcessor::determineNextColWord(int col, int colNum,
    const std::string &replaceVal, const std::string &word)
{
    return (col == colNum) ? replaceVal : word;
}

std::string CsvProcessor::getOutputWordDelimiter(int col)
{
    return (col == (numCols - 1)) ? "\n" : ",";
}
