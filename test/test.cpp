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

TEST_CASE( "Parse create table command", "[parser][table]" ) {
    Parser parser = Parser();
    CHECK_NOTHROW(parser.parse(test[0]));
    CHECK_NOTHROW(parser.parse(test[1]));
    CHECK_THROWS(parser.parse(test[2]));
    CHECK_THROWS(parser.parse(test[3]));
    CHECK_THROWS(parser.parse(test[4]));
    CHECK_THROWS(parser.parse(test[5]));
    CHECK_THROWS(parser.parse(test[6]));
    CHECK_THROWS(parser.parse(test[7]));
    CHECK_THROWS(parser.parse(test[8]));
};

