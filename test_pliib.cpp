#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "pliib.hpp"
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;
using namespace pliib;

TEST_CASE("fast split function performs as expected", "[split]"){

    char to_split [25] = "A;StrING;DeLIMITeD:.;by;";

    char** ret;
    int retsz;
    int* split_sizes;
    split(to_split, ';', ret, retsz, split_sizes);

    REQUIRE(retsz == 5);
    REQUIRE(strcmp(ret[0], "A") == 0);
}
