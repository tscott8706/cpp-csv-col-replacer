#include "CsvArgs.hpp"
#include "CsvProcessor.hpp"

int main(int argc, char *argv[])
{
    CsvArgs args(argc, argv);
    CsvProcessor processor(args.getInputData());
    std::string output = processor.replaceColVals(args.getColToOverwrite(),
        args.getColReplaceVal());
    args.setOutputData(output);
    return 0;
}
