//#include "commandChecker.h"
#include <iostream>
#include "DBMS.h"
#include <vector>
#include <regex>

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
    // 2 ("string", {some: object}) for commands, where first arg is table name, second some object with creatingData | createTable("example", {name: text, age: int});
    // 3 ({some: object}, {another: object})
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


class Parser {
private:
    regex firstTypeCommand = regex("^[a-zA-Z][a-zA-Z0-9]*\\(.*\\)");
    regex secondTypeCommand = regex(R"([a-zA-Z][a-zA-Z0-9]*\.[a-zA-Z][a-zA-Z0-9]*\(.*\))");
    string deleteSpacesFromString(string);
    string rawArgs;
    vector < CommandStruct > commands = {
            CommandStruct("createTable", 1, true, true, 2),
            CommandStruct("dropTable", 1, true, true, 0),
            CommandStruct("insert", 2, true, true, 1),
            CommandStruct("getOneRow", 2, true, true, 1),
            CommandStruct("getRows", 2, true, true, 1),
            CommandStruct("deleteRow", 2, true, true, 1),
            CommandStruct("deleteRows", 2, true, true, 1),
            CommandStruct("changeOneRowData", 2, true, true, 3),
            CommandStruct("changeData", 2, true, true, 3),
            CommandStruct("tables", 2, false, false),
            CommandStruct("display", 2, false, false),
    };
    vector < regex > argTypes {
            regex("\\\".*\\\""),
            regex("\\{.*\\:.*(,.*\\:.*)*?\\}"),
            regex("\\\".*\\\"\\,\\{.*\\:.*(\\,.*\\:.*)*?\\}"),
            regex("\\{.*\\:.*(\\,.*\\:.*)*?\\},\\{.*\\:.*(\\,.*\\:.*)*?\\}")
    };
public:
    Command parse(string);
    vector<Data> parseData(string);
    vector<string>split(string, char symb);
    void setRawArgs(string args);
    string getRawArgs();
    void parseRawArgs(int typeOfArgs, Command * item);
    void checkCommand(Command * item);
    bool checkTableFieldName(string str);
    bool checkDataType(string str);
    bool checkFieldType(string str);
};