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