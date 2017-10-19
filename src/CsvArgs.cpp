#include "CsvArgs.hpp"
#include <stdexcept>

CsvArgs::CsvArgs(int argc, char *argv[]):
    isInputOpen(false), isOutputOpen(false)
{
    parseCommandLine(argc, argv);
}

CsvArgs::~CsvArgs()
{
    if (isInputOpen)
    {
        inputFile.close();
    }
    if (isOutputOpen)
    {
        outputFile.close();
    }
}

std::istream &CsvArgs::getInputData()
{
    if (!isInputOpen)
    {
        inputFile.open(inputFname.c_str(), std::ifstream::in);
        checkFile(&inputFile, "input");
        isInputOpen = true;
    }
    return inputFile;
}

void CsvArgs::setOutputData(const std::string &data)
{
    if (!isOutputOpen)
    {
        outputFile.open(outputFname.c_str(), std::ofstream::out);
        checkFile(&outputFile, "output");
        isOutputOpen = true;
    }
    outputFile << data;
}

std::string CsvArgs::getColToOverwrite()
{
    return colToOverwrite;
}

std::string CsvArgs::getColReplaceVal()
{
    return colReplaceVal;
}

void CsvArgs::parseCommandLine(int argc, char *argv[])
{
    const int programName = 1;
    const int requiredUserArgs = 4;
    const int requiredArgs = programName + requiredUserArgs;

    if (argc != requiredArgs)
    {
        throw std::invalid_argument("Usage: ./colReplacer inputData "
            "colToOverwrite colReplaceVal outputData\n");
    }

    inputFname = argv[1];
    colToOverwrite = argv[2];
    colReplaceVal = argv[3];
    outputFname = argv[4];
}

void CsvArgs::checkFile(const std::ios *fileHandler,
    const std::string &fileType)
{
    if (!fileHandler->good())
    {
        throw std::invalid_argument("Could not open " + fileType + " file.\n");
    }
}
