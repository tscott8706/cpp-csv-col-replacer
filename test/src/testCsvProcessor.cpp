#include "catch.hpp"
#include "CsvProcessor.hpp"
#include <sstream>

TEST_CASE("Empty data should throw exception: 'input data missing'")
{
    std::istringstream inputData;
    REQUIRE_THROWS(CsvProcessor(inputData).replaceColVals("col1", "val1"));
}

TEST_CASE("Column not found should throw exception: 'column name doesn't "
    "exist in the input data'")
{
    std::istringstream inputData("col1,col2,col3\nval1,val2,val3");
    REQUIRE_THROWS(CsvProcessor(inputData).replaceColVals("badColHeader",
        "myval"));
}

TEST_CASE("Different num columns (too few) in input data throws exception: "
    "'input file is malformed'")
{
    std::istringstream inputData("col1,col2,col3\nval1,val2,val3\nthisRow,hasNoThirdCol");
    REQUIRE_THROWS(CsvProcessor(inputData).replaceColVals("col1", "myval"));
}

TEST_CASE("Different num columns (too many) in input data throws exception: "
    "'input file is malformed'")
{
    std::istringstream inputData("col1,col2,col3\nval1,val2,val3\n"
        "val1,val2,val3,extraCol");
    REQUIRE_THROWS(CsvProcessor(inputData).replaceColVals("col1", "myval"));
}

TEST_CASE("replaceColVals replaces all column values with a value")
{
    std::istringstream inputData
    (
        "col1," "replaceCol," "col3\n"
        "val1," "val2,"       "val3\n"
        "val1," "val5,"       "val6\n"
    );
    std::string output = CsvProcessor(inputData).replaceColVals("replaceCol",
        "myval");
    std::string expected_output =
    (
        "col1," "replaceCol," "col3\n"
        "val1," "myval,"      "val3\n"
        "val1," "myval,"      "val6\n"
    );
    REQUIRE(output == expected_output);
}
