#include "Command.h"

int Command::getCommandType() {
    return commandType;
}

void Command::setCommandType(int type) {
    commandType = type;
}

string Command::getCommand() {
    return command;
}

void Command::setCommand(string command) {
    this->command = command;
}

vector < Data >  Command::getDataToFind() {
    return dataToFind;
}

void Command::setDataToFind(vector < Data > data) {
    this->dataToFind = data;
}

vector < Data >  Command::getDataToInsert() {
    return dataToInsert;
}

void Command::setDataToInsert(vector < Data > data) {
    this->dataToInsert = data;
}

string Command::getTableName(){
    return tableName;
}

void Command::setTableName(string tableName){
    this->tableName = tableName;
}

string Command::getRawArgs(){
    return rawArgs;
}

void Command::setRawArgs(string rawArgs){
    this->rawArgs = rawArgs;
}

void Command::parseRawArgs(int typeOfArgs){
    if (rawArgs == ""){
        cout << "no args" << endl;
        return;
    }
    if(regex_match(rawArgs, argTypes[typeOfArgs])){
        if((typeOfArgs) == 0){
            setTableName(rawArgs.substr(1, rawArgs.length() - 2));
        }
        else if (typeOfArgs == 1) {
            setDataToInsert(parseData(rawArgs.substr(1, rawArgs.length() - 2)));
        } else if (typeOfArgs == 2 || typeOfArgs == 3) {
            string name, object;
            for (int i = 0; i < rawArgs.length(); ++i) {
                if(rawArgs[i] == ','){
                    name = rawArgs.substr(1, i-2);
                    object = rawArgs.substr(i+1, rawArgs.length() - 1);
                    break;
                }
            }
            setTableName(name);
            cout << "tableNameAdded" << getTableName() << endl;
            setDataToInsert(parseData(object.substr(1, object.length() - 2)));
        }
        else if (typeOfArgs == 4) {
            string object1, object2;
            for (int i = 0; i < rawArgs.length(); ++i) {
                if(rawArgs[i] == '}'){
                    i++;
                    object1 = rawArgs.substr(1, i-2);
                    object2 = rawArgs.substr(i+2, rawArgs.length() - (i + 3));
                    cout << rawArgs << " Check" << endl;
                    cout << object2 << " Check" << endl;
                    break;
                }
            }
            setDataToFind(parseData(object1));
            setDataToInsert(parseData(object2));
        }
    } else {
      throw UndefinedError();
    }
}