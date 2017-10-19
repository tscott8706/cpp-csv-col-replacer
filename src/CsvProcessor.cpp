#include "CsvArgs.hpp"
#include "CsvProcessor.hpp"
#include <stdexcept>

CsvProcessor::CsvProcessor(CsvArgs &args):
    args(args), numCols(0), COL_NOT_FOUND(-1)
{
}

void CsvProcessor::replaceColValues()
{
    int colNum = findColToReplace(args.getColToOverwrite());
    *args.getOutputData() << colHeaders << std::endl;
    replaceAllCols(colNum, args.getColReplaceVal());
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
    if (!args.getInputData()->good())
    {
        throw std::invalid_argument("Could not open input file\n");
    }

    if (!getline(*args.getInputData(), colHeaders))
    {
        throw std::invalid_argument("input data missing\n");
    }
}

void CsvProcessor::replaceAllCols(int colNum, std::string replaceVal)
{
    std::string line;
    std::string word;

    while (getline(*args.getInputData(), line))
    {
        std::istringstream colProcessor(line);
        for (int col = 0; col < numCols; col++)
        {
            if (!getline(colProcessor, word, ','))
            {
                throw std::invalid_argument("Input file is malformed.  " +
                    line + "does not have correct number of columns.");
            }

            *args.getOutputData() <<
                determineNextColWord(col, colNum, replaceVal, word) <<
                getOutputWordDelimiter(col);
        }
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
