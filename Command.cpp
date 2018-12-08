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

string Command::getData() {
    return data;
}

void Command::setData(string data) {
    this->data = data;
}

string Command::getTableName(){
    return tableName;
}

void Command::setTableName(string tableName){
    this->tableName = tableName;
}