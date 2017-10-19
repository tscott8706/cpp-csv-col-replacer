#include "catch.hpp"
#include "CsvArgs.hpp"
#include "CsvProcessor.hpp"
#include <ostream>
#include <sstream>

bool is_ostream_empty(std::ostream *output)
{
    std::stringstream ss;
    ss << output->rdbuf();
    return (ss.str() == "");
}

TEST_CASE("Empty data should throw exception: 'input data missing' and no "
    "output data")
{
    CsvArgs args("", "Age", "99");
    REQUIRE_THROWS(CsvProcessor(args).replaceColValues());
    REQUIRE(is_ostream_empty(args.getOutputData()));
}

TEST_CASE("Column not found should throw exception: 'column name doesn't "
    "exist in the input data' and no output data")
{
    CsvArgs args("col1,col2,col3\nval1,val2,val3", "col4", "myval");
    REQUIRE_THROWS(CsvProcessor(args).replaceColValues());
    REQUIRE(is_ostream_empty(args.getOutputData()));
}

