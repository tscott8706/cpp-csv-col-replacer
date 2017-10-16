#include "CsvArgs.hpp"
#include "CsvProcessor.hpp"

int main(int argc, char *argv[])
{
    const bool IN_AND_OUT_ARE_FILES = true;
    CsvArgs args(argc, argv, IN_AND_OUT_ARE_FILES);
    CsvProcessor processor(args);
    processor.replaceColValues();
    return 0;
}
