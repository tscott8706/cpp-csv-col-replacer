#include "catch.hpp"
#include "CsvArgs.hpp"

char programName[] = "colReplacer";

// Normally from the command-line, these are files.  However, the code has been
// written in a way so that these can be files or strings and both are
// processed the same way.
char inputData[] = "col1,col2,col3\na,b,c\nd,e,f";
char outputData[] = "ignored";

char colToOverwrite[] = "ColHeader";
char colReplaceVal[] = "ReplaceVal";

char* argv[] = {&programName[0], &inputData[0], &colToOverwrite[0],
    &colReplaceVal[0], &outputData[0], NULL};

const bool NOT_A_FILE = false;

TEST_CASE("CsvArgs constructor throws exception when number of args is not "
    "four")
{
    int argc = 4;
    REQUIRE_THROWS(CsvArgs(argc, argv, NOT_A_FILE));
}

TEST_CASE("CsvArgs puts command-line args into member variables")
{
    int argc = 5;
    CsvArgs args(argc, argv, NOT_A_FILE);

    std::string input;
    getline(*args.getInputData(), input);
    REQUIRE(input == "col1,col2,col3");
    REQUIRE(args.getColToOverwrite() == std::string(colToOverwrite));
    REQUIRE(args.getColReplaceVal() == std::string(colReplaceVal));
}

