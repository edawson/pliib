#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "pliib.hpp"
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;
using namespace pliib;

TEST_CASE("fast split function performs as expected", "[split]"){

    char* to_split = new char[26];
    strcpy(to_split, ";A;StrING;DeLIMITeD:.;by;");
    to_split[25] = '\0';

    SECTION("The countChar function works as expected"){
        std::size_t num;
        countChar(to_split, ';', num);
        REQUIRE(num == 5);
    }

    char** ret;
    std::size_t retsz;
    int* split_sizes;
    split(to_split, ';', ret, retsz, split_sizes);

    //for (int i = 0; i < retsz; ++i){

    //    cout << '"' << ret[i] << '"' << endl;
    //}


    REQUIRE(retsz == 6);
    REQUIRE(strlen(ret[0]) == 0);
    REQUIRE(strcmp(ret[1], "A") == 0);
    REQUIRE(strcmp(ret[2], "StrING") == 0);
    REQUIRE(split_sizes[3] == 11);
    REQUIRE(split_sizes[0] == 0);
    REQUIRE(split_sizes[1] == 1);

    SECTION("split works for strings"){
        string s = "ANOTHER:Separated:String";
        vector<string> ret;
        split(s, ':', ret);
        REQUIRE(ret.size() == 3);
        REQUIRE(ret[0].compare("ANOTHER") == 0);
        REQUIRE(ret[2].compare("String") == 0);
    }

    delete[] to_split;
}
