#include "catch.hpp"
#include "CsvArgs.hpp"

char programName[] = "colReplacer";

char inputData[] = "in.csv";
char outputData[] = "out.csv";

char colToOverwrite[] = "ColHeader";
char colReplaceVal[] = "ReplaceVal";

char* argv[] = {&programName[0], &inputData[0], &colToOverwrite[0],
    &colReplaceVal[0], &outputData[0], NULL};

TEST_CASE("CsvArgs constructor throws exception when number of args is not "
    "four")
{
    int argc = 4;
    REQUIRE_THROWS(CsvArgs(argc, argv));
}

TEST_CASE("CsvArgs puts command-line args into member variables")
{
    int argc = 5;
    CsvArgs args(argc, argv);

    REQUIRE(args.getColToOverwrite() == std::string(colToOverwrite));
    REQUIRE(args.getColReplaceVal() == std::string(colReplaceVal));
}

