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
        throw NoArguments();
    }
    if(regex_match(rawArgs, argTypes[typeOfArgs])){
        if((typeOfArgs) == 0){
            string temp = rawArgs.substr(1, rawArgs.length() - 2);
            if(!regex_match(temp, regex("[a-zA-Z][a-zA-Z0-9]*"))){
                throw StringError();
            }
            setTableName(temp);
        }
        else if (typeOfArgs == 1) {
            vector < Data > temp = parseData(rawArgs.substr(1, rawArgs.length() - 2));
            for(Data item : temp) {
                if(!regex_match(item.fieldName, regex("[a-zA-Z][a-zA-Z0-9]*"))){
                    throw StringError();
                }
                if(!regex_match(item.data, regex(R"(((\".*\")|(true)|(false)|([0-9]*(\.)?[0-9]*)))"))){
                    throw typeError(item.data);
                }
            }
            setDataToInsert(temp);
        } else if (typeOfArgs == 3) {
            string name, object;
            for (int i = 0; i < rawArgs.length(); ++i) {
                if(rawArgs[i] == ','){
                    name = rawArgs.substr(1, i-2);
                    object = rawArgs.substr(i+1, rawArgs.length() - 1);
                    break;
                }
            }
            if(!regex_match(name, regex("[a-zA-Z][a-zA-Z0-9]*"))){
                throw StringError();
            }
            vector < Data > temp = parseData(object.substr(1, object.length() - 2));
            for(Data item : temp) {
                if(!regex_match(item.fieldName, regex("[a-zA-Z][a-zA-Z0-9]*"))){
                    throw StringError();
                }
                if(!regex_match(item.data, regex(R"((int)|(short)|(float)|(text)|(tinyText)|(bool))"))){
                    throw dataTypeError(item.data);
                }
            }
            setTableName(name);
            setDataToInsert(temp);
        }
        else if (typeOfArgs == 4) {
            string object1, object2;
            for (int i = 0; i < rawArgs.length(); ++i) {
                if(rawArgs[i] == '}'){
                    i++;
                    object1 = rawArgs.substr(1, i-2);
                    object2 = rawArgs.substr(i+2, rawArgs.length() - (i + 3));
                    break;
                }
            }
            vector < Data > temp1 = parseData(object1);
            vector < Data > temp2 = parseData(object2);

            for(Data item : temp1) {
                if(!regex_match(item.fieldName, regex("[a-zA-Z][a-zA-Z0-9]*"))){
                    throw StringError();
                }
                if(!regex_match(item.data, regex(R"(((\".*\")|(true)|(false)|([0-9]*(\.)?[0-9]*)))"))){
                    throw dataTypeError(item.data);
                }
            }


            for(Data item : temp2) {
                if(!regex_match(item.fieldName, regex("[a-zA-Z][a-zA-Z0-9]*"))){
                    throw StringError();
                }
                if(!regex_match(item.data, regex(R"(((\".*\")|(true)|(false)|([0-9]*(\.)?[0-9]*)))"))){
                    throw dataTypeError(item.data);
                }
            }
            setDataToFind(temp1);
            setDataToInsert(temp2);
        }
    } else {
      throw WrongArgument(typeOfArgs);
    }
}