#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "pliib.hpp"
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdint>

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
    std::size_t* split_sizes;
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

TEST_CASE("pliib can fill arrays using its fill_array function", "[fill_array]"){
	int* x = new int[25];
	x[0] = 1;
	pliib::fill_array(x, 0, 25);
	REQUIRE(x[0] == 0);
	REQUIRE(x[10] == 0);

	delete [] x;
	
	uint64_t* x_long = new uint64_t[1000];
	pliib::fill_array<uint64_t>(x_long, 0, 1000);
	REQUIRE(x_long[0] == 0);
	REQUIRE(x_long[100] == 0);
	pliib::fill_array<uint64_t>(x_long, 10, 1000);
	REQUIRE(x_long[0] == 10);
	REQUIRE(x_long[100] == 10);
	delete [] x_long;

}

TEST_CASE("is_numeric_string performs as expected.", "[is_numeric_string]"){
    char* s = "12345";
    char* t = "12Eg5";
    REQUIRE(is_numeric_string(s) == true);
    REQUIRE(is_numeric_string(t) == false);
}

TEST_CASE("reversing a string produces the expected results", "[reverse]"){
    std::string pre ("AAATTGGCC");
    std::string pre_long ("AAATTGGCCAAAAAAGGG");
    char* sr;
    char* sr_long;
    pliib::strcopy(pre.c_str(), sr);
    pliib::strcopy(pre.c_str(), sr_long);
    pliib::reverse_inplace(sr, 9);
    pliib::reverse_inplace(sr_long, 9);
    char* sr_long_sub;
    pliib::substr(sr_long, 0, 9, sr_long_sub);
    REQUIRE(strcmp(sr, "CCGGTTAAA") == 0);
    REQUIRE(strcmp(sr_long_sub, "CCGGTTAAA") == 0);
}
