#ifndef CSV_ARG_HANDLER_H
#define CSV_ARG_HANDLER_H

#include <fstream>
#include <istream>
#include <sstream>
#include <string>

class CsvArgs
{
public:
    CsvArgs(const std::string &input, const std::string &colToOverwrite,
        const std::string &colReplaceVal);
    CsvArgs(int argc, char *argv[], bool isFile = true);
    ~CsvArgs();
    CsvArgs(const CsvArgs& that) = delete;

    std::istream *getInputData();
    std::ostream *getOutputData();
    std::string getColToOverwrite();
    std::string getColReplaceVal();

private:
    void parseCommandLine(int argc, char *argv[], std::string &input,
        std::string &output);
    void setDataStreams(const std::string &input, const std::string &output);
    void checkFile(const std::ios *fileHandler, const std::string &fileType);

    std::istream *inputData;
    std::ostream *outputData;
    std::string colToOverwrite;
    std::string colReplaceVal;
    std::istringstream inputStringStream;
    std::ostringstream outputStringStream;
    std::ifstream inputFile;
    std::ofstream outputFile;
    bool isFile;
};
typedef struct CsvArgs CsvArgs;

#endif
