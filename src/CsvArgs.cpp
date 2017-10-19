#include "CsvArgs.hpp"
#include <stdexcept>
#include <iostream>

CsvArgs::CsvArgs(const std::string &input, const std::string &colToOverwrite,
    const std::string &colReplaceVal):
    inputData(NULL), outputData(NULL), colToOverwrite(colToOverwrite),
    colReplaceVal(colReplaceVal), isFile(false)
{
    setDataStreams(input, "");
}

CsvArgs::CsvArgs(int argc, char *argv[], bool isFile):
    inputData(NULL), outputData(NULL), isFile(isFile)
{
    std::string input;
    std::string output;
    parseCommandLine(argc, argv, input, output);
    setDataStreams(input, output);
}

CsvArgs::~CsvArgs()
{
    if (isFile)
    {
        inputFile.close();
        outputFile.close();
    }

    inputData = NULL;
    outputData = NULL;
}

std::istream *CsvArgs::getInputData()
{
    return inputData;
}

std::ostream *CsvArgs::getOutputData()
{
    return outputData;
}

std::string CsvArgs::getColToOverwrite()
{
    return colToOverwrite;
}

std::string CsvArgs::getColReplaceVal()
{
    return colReplaceVal;
}

void CsvArgs::parseCommandLine(int argc, char *argv[], std::string &input,
        std::string &output)
{
    const int programName = 1;
    const int requiredUserArgs = 4;
    const int requiredArgs = programName + requiredUserArgs;

    if (argc != requiredArgs)
    {
        throw std::invalid_argument("Usage: ./colReplacer inputData "
            "colToOverwrite colReplaceVal outputData\n");
    }

    input = argv[1];
    colToOverwrite = argv[2];
    colReplaceVal = argv[3];
    output = argv[4];
}

void CsvArgs::setDataStreams(const std::string &input,
    const std::string &output)
{
    if (isFile)
    {
        inputFile.open(input.c_str(), std::ifstream::in);
        outputFile.open(output.c_str(), std::ofstream::out);
        checkFile(&inputFile, "input");
        checkFile(&outputFile, "output");

        inputData = &inputFile;
        outputData = &outputFile;
    }
    else
    {
        inputStringStream.str(input);
        // Output passed in is ignored if we aren't using files.

        inputData = &inputStringStream;
        outputData = &outputStringStream;
    }
}

void CsvArgs::checkFile(const std::ios *fileHandler,
    const std::string &fileType)
{
    if (!fileHandler->good())
    {
        throw std::invalid_argument("Could not open " + fileType + " file.\n");
    }
}
