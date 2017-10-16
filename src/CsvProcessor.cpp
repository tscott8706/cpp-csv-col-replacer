#include "CsvArgs.hpp"
#include "CsvProcessor.hpp"
#include <iostream>

CsvProcessor::CsvProcessor(CsvArgs &args): args(args), numCols(0)
{
}

CsvProcessor::~CsvProcessor()
{
}

bool CsvProcessor::replaceColValues()
{
    int colNum = findColNum(args.getColToOverwrite());
    replaceAllCols(colNum, args.getColReplaceVal());
    return true;
}

int CsvProcessor::findColNum(std::string headerName)
{
    const int NOT_FOUND = -1;
    int colNum = NOT_FOUND;

    if (!getColHeaders())
    {
        return NOT_FOUND;
    }

    std::istringstream colHeaderProcessor(colHeaders);
    std::string colHeader;

    do
    {
        if (!getline(colHeaderProcessor, colHeader, ','))
        {
            break;
        }
        else if (colHeader == headerName)
        {
            colNum = numCols;
        }
        numCols++;
    } while (colHeaderProcessor);

    return colNum;
}

bool CsvProcessor::getColHeaders()
{
    if (!args.getInputData()->good())
    {
        return false;
    }

    if (!getline(*args.getInputData(), colHeaders))
    {
        return false;
    }

    return true;
}

bool CsvProcessor::replaceAllCols(int colNum, std::string replaceVal)
{
    std::string line;
    std::string word;
    *args.getOutputData() << colHeaders << std::endl;

    while (getline(*args.getInputData(), line))
    {
        std::istringstream colProcessor(line);
        for (int col = 0; col < numCols; col++)
        {
            if (!getline(colProcessor, word, ','))
            {
                std::cout << "bad\n";
                return false;
            }

            if (col == colNum)
            {
                *args.getOutputData() << replaceVal;
            }
            else
            {
                *args.getOutputData() << word;
            }
            if (col == numCols - 1)
            {
                *args.getOutputData() << std::endl;
            }
            else
            {
                *args.getOutputData() << ',';
            }
        }
    }

    return false;
}
