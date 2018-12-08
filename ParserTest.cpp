#include "ParserTest.h"

void ParserTest(){
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
    Parser parser = Parser();
    for(string i : test){
        cout << i << endl;
        try{
            parser.parse(i);
            cout << " + " << endl;
        } catch (ParserError e){
            e.showError();
        }
        cout << "=============================================================================================" << endl;
    }
}