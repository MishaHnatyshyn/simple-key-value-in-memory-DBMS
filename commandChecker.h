#include <iostream>
#include "DBMS.h"
#include <vector>

using namespace std;

struct CommandStruct {
    string name;
    int commandType;
    //1 -> command(...)
    //2 -> tableName.command(...)
    bool shouldHaveArgs; //set to false if you have no args in command | showTableNames(), table.display();
    bool shouldHaveTableName; //set to false if you don't need table name | showTableNames();
    int argsTypeNumber;
    // 0 ("someString") for command, where you need table name | deleteTable("example")
    // 1 ({some: object}) for commands to insert something | table.insert({name: "Misha"})
    // 2 not used and reserved for something
    // 3 ("string", {some: object}) for commands, where first arg is table name, second some object with creatingData | createTable("example", {name: text, age: int});
    // 4 ({some: object}, {another: object})
    // do not even try to break something bitch!

    CommandStruct(string name, int commandType, bool shouldHaveArgs, bool shouldHaveTableName, int argsTypeNumber):
    name(name),commandType(commandType),shouldHaveArgs(shouldHaveArgs),shouldHaveTableName(shouldHaveTableName),argsTypeNumber(argsTypeNumber){};

    CommandStruct(string name, int commandType, bool shouldHaveArgs, bool shouldHaveTableName):
            name(name),commandType(commandType),shouldHaveArgs(shouldHaveArgs),shouldHaveTableName(shouldHaveTableName){
        if(shouldHaveArgs == 1){
            cout << "Should have args!" << endl;
        }
    };
};

class CommandChecker {
     vector < CommandStruct > commands = {
             CommandStruct("createTable", 1, 1, 1, 3),
             CommandStruct("dropTable", 1, 1, 1, 0),
             CommandStruct("insert", 2, 1, 1, 1),
             CommandStruct("getOneRow", 2, 1, 1, 1),
             CommandStruct("getRows", 2, 1, 1, 1),
             CommandStruct("deleteRow", 2, 1, 1, 1),
             CommandStruct("deleteRows", 2, 1, 1, 1),
             CommandStruct("changeOneRowData", 2, 1, 1, 4),
             CommandStruct("changeData", 2, 1, 1, 4),
             CommandStruct("tables", 2, 0, 0),
             CommandStruct("display", 2, 0, 1),
     };
public:
    void checkCommand(Command * item){
         for (CommandStruct i : commands){
             if(i.name == item->getCommand()) {
                 if(i.commandType != item->getCommandType()) throw NoSuchCommand();
                 if(!i.shouldHaveArgs && item->getRawArgs().length()) throw MustNotHaveArgs();
                 if (i.shouldHaveArgs) item->parseRawArgs(i.argsTypeNumber);
                 if (i.shouldHaveTableName && item->getTableName() == ""){
                     throw NoTableName();
                 }
                 return;
             }
         }
        throw NoSuchCommand();
    }
};
