#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Parser.h"
//#include "../gtest/gtest.h"


int sum(int a, int b){
    return a + b;
}
vector < string > test = {
        "createTable(\"Example\")",
        "createTable(\"Example\", {name: text, age: int})",
        "create.Table(\"Example\", {name: string, age: int})",
        "create.Table(\"Example\", {name: string, age: int, ega})",
        "$createTable(\"Example\", {name: string, age: int})",
        "createTable(\"Example\", (name: string, age: int))",
        "createTable(\'Example\', (name: string, age: int))",
        "createTable(\"Example\", {name: string; age: int})",
        "createTable(\"Example\", (name= string, age: int))",
        "createTable(\"Examp\"le, {name: string, age: int})",
        "createTable(\"Example\", {name: string, age: int}=)",


        "example.insert({name: \"   misha   \", age:   18)}",
        "example.insert({name: \"   misha   \"})",
        "examp124le.insert({name: \"   misha   \"}, age:   18)",
        "example.insert({name$: \"   misha   \"}, age:   18)",
        "example.insert({name: \"   misha   \"}, age:   18, agw)",
        "example.insert({name: \"   misha   \"}, age:   18, age: )",
        "example.insert({name: \"   misha   \"}, ag e:   18)",
        "example.insert( safname: \"   misha   \"}, age:   18)",
        "example.insert}(name: \"   misha   \"}, age:   18)",
        "example.insert({name: \"   misha   \"}, age:   18)",
        "example.insergast({name: \"   misha   \", age:   18)}",
        "example.insert({name: \"   misha   \", age:   helpMe)}",
        "example.insert({name: \"   misha   \", age:   69741.asf)}",
        "example.insert({name: \"   misha   \", age:   69741.asf})",

};

TEST_CASE( "Parse valid create table command", "[correct][parser][table]" ) {
    Parser parser = Parser();
    CHECK_THROWS(parser.parse(test[0]));
    CHECK_NOTHROW(parser.parse(test[1]));
};

TEST_CASE( "Parse invalid create table command", "[incorrect][parser][table]" ) {
    Parser parser = Parser();
    CHECK_THROWS(parser.parse(test[2]));
    CHECK_THROWS(parser.parse(test[3]));
    CHECK_THROWS(parser.parse(test[4]));
    CHECK_THROWS(parser.parse(test[5]));
    CHECK_THROWS(parser.parse(test[6]));
    CHECK_THROWS(parser.parse(test[7]));
    CHECK_THROWS(parser.parse(test[8]));
};


// TYPE CASTING TESTS


// CUSTOM INT

TEST_CASE("Casting valid string to int", "[type][int][casting]"){
    REQUIRE(CustomInt("5").get() == 5);
    REQUIRE(CustomInt("21").get() == 21);
    REQUIRE(CustomInt("55").get() == 55);
    REQUIRE(CustomInt("378").get() == 378);
    REQUIRE(CustomInt("37502").get() != 387);
}

TEST_CASE("Custom int toString() method", "[type][int][casting]"){
    REQUIRE(CustomInt("5").toString() == "5");
    REQUIRE(CustomInt("21").toString() == "21");
    REQUIRE(CustomInt("55").toString() == "55");
    REQUIRE(CustomInt("378").toString() == "378");
}

TEST_CASE("Casting invalid string to int", "[type][int][casting]"){
    CHECK_THROWS(CustomInt("true"));
    CHECK_THROWS(CustomInt("false"));
    CHECK_THROWS(CustomInt("ebat'"));
    CHECK_THROWS(CustomInt("yobaniy v rot"));
    CHECK_THROWS(CustomInt("4.55"));
}

// CUSTOM FLOAT

TEST_CASE("Casting valid string to float", "[type][float][casting]"){
    REQUIRE(CustomFloat("5.0").get() == 5.0f);
    REQUIRE(CustomFloat("55.564").get() == 55.564f);
    REQUIRE(CustomFloat("21.4").get() == 21.4f);
    REQUIRE(CustomFloat("378.54444").get() == 378.54444f);
    REQUIRE(CustomFloat("37502.54654654").get() != 32.4654f);
}


TEST_CASE("Custom float toString() method", "[type][float][casting]"){
    REQUIRE(CustomFloat("55.564").toString() == "55.564");
    REQUIRE(CustomFloat("5.0").toString() == "5.0");
    REQUIRE(CustomFloat("21.4").toString() == "21.4");
    REQUIRE(CustomFloat("378.54444").toString() == "378.54444");
}

TEST_CASE("Casting invalid string to float", "[type][float][casting]"){
    CHECK_THROWS(CustomInt("true"));
    CHECK_THROWS(CustomInt("false"));
}

// CUSTOM SHORT

TEST_CASE("Casting valid string to short", "[type][short][casting]"){
    REQUIRE(CustomShort("5").get() == 5);
    REQUIRE(CustomShort("21").get() == 21);
    REQUIRE(CustomShort("55").get() == 55);
    REQUIRE(CustomShort("378").get() == 378);
    REQUIRE(CustomShort("37502").get() != 387);
}


TEST_CASE("Casting too large int in string to short", "[type][short][casting]"){
    CHECK_THROWS(CustomShort("327678"));
    CHECK_THROWS(CustomShort("327679"));
    CHECK_THROWS(CustomShort("327677327677"));
    CHECK_THROWS(CustomShort("-327678"));
    CHECK_THROWS(CustomShort("-327679"));
}

TEST_CASE("Casting invalid string to short", "[type][float][casting]"){
    CHECK_THROWS(CustomShort("true"));
    CHECK_THROWS(CustomShort("false"));
}

// CUSTOM STRING

TEST_CASE("Casting valid string to string", "[type][short][casting]"){
    REQUIRE(CustomString("Sdfsdf").get() == "Sdfsdf");
    REQUIRE(CustomString("SDFsdfsd sd fasdfas ").get() == "SDFsdfsd sd fasdfas ");
    REQUIRE(CustomString("sdfsd SDF sdfs SDff").get() == "sdfsd SDF sdfs SDff");
    REQUIRE(CustomString("sdfs sd fsaf ").get() == "sdfs sd fsaf ");
    REQUIRE(CustomString("asdf af asdfsdsdfdd").get() != "asdsdaf f af asdfsdsdfdd");
}


