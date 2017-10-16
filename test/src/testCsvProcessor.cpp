#include "catch.hpp"
#include "CsvArgs.hpp"
#include "CsvProcessor.hpp"

TEST_CASE("Empty data should throw exception: 'input file missing'")
{
    int argc = 5;
    char emptyInputData[] = "";
    char* emptyInputArgv[] = {&programName[0], &emptyInputData[0],
        &colToOverwrite[0], &colReplaceVal[0], &outputData[0], NULL};

    REQUIRE_THROWS(CsvArgs(argc, emptyInputArgv, NOT_A_FILE));
}

TEST_CASE("Column not found should throw exception: 'column name doesn't "
    "exist in the input file'")
{
    int argc = 5;
    char emptyInputData[] = "";
    char* emptyInputArgv[] = {&programName[0], &emptyInputData[0],
        &colToOverwrite[0], &colReplaceVal[0], &outputData[0], NULL};

    REQUIRE_THROWS(CsvArgs(argc, emptyInputArgv, NOT_A_FILE));
}

TEST_CASE("replaceColValues with invalid input file throws exception")
{
    //CsvArgs("unused.csv", "unused", "unused", "unused.csv");
}
