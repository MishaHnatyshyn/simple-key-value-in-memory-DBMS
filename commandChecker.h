#include <iostream>
#include "DBMS.h"
#include <vector>

using namespace std;

struct CommandStruct {
    string name;
    bool shouldHaveArgs; //set to false if you have no args in command | showTableNames(), table.display();
    bool shouldHaveTableName; //set to false if you don't need table name | showTableNames();
    int argsTypeNumber;
    // 0 ("someString") for command, where you need table name | deleteTable("example")
    // 1 ({some: object}) for commands to insert something | table.insert({name: "Misha"})
    // 2 ("string", {some: object}) for commands, where first arg is table name, second some object with data | createTable("example", {name: "misha". age: 18);
    // 3 ("string", {some: object}) for commands, where first arg is table name, second some object with creatingData | createTable("example", {name: text, age: int});
    // 4 ({some: object}, {another: object})
    // do not even try to break something bitch!

    CommandStruct(string name, bool shouldHaveArgs, bool shouldHaveTableName, int argsTypeNumber):
    name(name),shouldHaveArgs(shouldHaveArgs),shouldHaveTableName(shouldHaveTableName),argsTypeNumber(argsTypeNumber){};

    CommandStruct(string name, bool shouldHaveArgs, bool shouldHaveTableName):
            name(name),shouldHaveArgs(shouldHaveArgs),shouldHaveTableName(shouldHaveTableName){
        if(shouldHaveArgs == 1){
            cout << "Should has args!";
        }
    };
};

class CommandChecker {
     vector < CommandStruct > commands = {
             CommandStruct("createTable", 1, 1, 3),
             CommandStruct("insert", 1, 1, 1),
             CommandStruct("tables", 0, 0),
             CommandStruct("delete", 1, 1, 0),
             CommandStruct("display", 0, 1),
     };
public:
    void checkCommand(Command * item){
         for (CommandStruct i : commands){
             if(i.name == item->getCommand()) {
                 if (i.shouldHaveArgs) item->parseRawArgs(i.argsTypeNumber);
                 if(i.shouldHaveTableName && item->getTableName() == ""){
                     throw NoTableName();
                 }
                 return;
             }
         }
        throw UndefinedError();
    }
};
