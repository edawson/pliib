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
    to_split[24] = '\0';

    SECTION("The countChar function works as expected"){
        int num;
        countChar(to_split, ';', num);
        REQUIRE(num == 4);
    }

    char** ret;
    int retsz;
    int* split_sizes;
    split(to_split, ';', ret, retsz, split_sizes);

    for (int i = 0; i < retsz; ++i){

        cout << '"' << ret[i] << '"' << endl;
    }


    REQUIRE(retsz == 5);
    REQUIRE(strcmp(ret[0], "A") == 0);
    REQUIRE(strcmp(ret[1], "StrING") == 0);
//    REQUIRE(split_sizes[2] == 11);
    REQUIRE(split_sizes[0] == 1);
}
