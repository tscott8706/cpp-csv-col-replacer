#ifndef CSV_ARG_HANDLER_H
#define CSV_ARG_HANDLER_H

#include <fstream>
#include <istream>
#include <string>

class CsvArgs
{
public:
    CsvArgs(int argc, char *argv[]);
    ~CsvArgs();
    CsvArgs(const CsvArgs& that) = delete;

    std::istream &getInputData();
    void setOutputData(const std::string &data);
    std::string getColToOverwrite();
    std::string getColReplaceVal();

private:
    void parseCommandLine(int argc, char *argv[]);
    void checkFile(const std::ios *fileHandler, const std::string &fileType);

    std::string colToOverwrite;
    std::string colReplaceVal;
    std::ifstream inputFile;
    std::ofstream outputFile;
    std::string inputFname;
    std::string outputFname;
    bool isInputOpen;
    bool isOutputOpen;
};
typedef struct CsvArgs CsvArgs;

#endif
