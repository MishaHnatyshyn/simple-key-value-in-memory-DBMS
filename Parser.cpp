#include "Parser.h"

vector<string> Parser::split(string str,char symb){
    vector<string> result;
    int start = 0 , length = 0;
    for (int i = 0; i <= str.length(); ++i) {
        if (str[i] == symb || i == str.length()){
            length = i - start;
            string temp = str.substr(start,length);
            start +=length + 1;
            result.push_back(temp);
        }
    }
    return result;
}

vector<Data> Parser::parseData(string data) {
    vector<Data> result;
    for(string i : split(data, ',')){
        vector <string > temp = split(i, ':');
        result.push_back(Data(temp[0], temp[1]));
    }
    return result;
}

string Parser::deleteSpacesFromString(string str) {
    for(int i = 0; i < str.length(); i++){
        if(str[i] == '"'){
            i++;
            while(str[i] != '"' && i < str.length()){
                i++;
            }
            i++;
        }
        else if(str[i] == ' '){
            int length = 0;
            int start = i;
            while(str[i] == ' ') { length++; i++; }
            str.replace(start, length, "");
            i-= length + 1;
        }
    }
    return str;
}

void Parser::checkCommand(Command *item) {
    for (CommandStruct i : commands){
        if(i.name == item->getCommand()) {
            if(i.commandType != item->getCommandType()) throw NoSuchCommand();
            if(!i.shouldHaveArgs && getRawArgs().length()) throw MustNotHaveArgs();
            if (i.shouldHaveArgs) parseRawArgs(i.argsTypeNumber, item);
            if (i.shouldHaveTableName && item->getTableName() == ""){
                throw NoTableName();
            }
            return;
        }
    }
    throw NoSuchCommand();
}

void Parser::setRawArgs(string args) {
    rawArgs = args;
}

string Parser::getRawArgs() {
    return rawArgs;
}

bool Parser::checkDataType(string str) {
    return regex_match(str, regex(R"(((\".*\")|(true)|(false)|([0-9]*(\.)?[0-9]*)))"));
}

bool Parser::checkTableFieldName(string str) {
    return regex_match(str, regex("[a-zA-Z][a-zA-Z0-9_]*"));
}

bool Parser::checkFieldType(string str){
    return regex_match(str, regex(R"((int)|(short)|(float)|(text)|(tinytext)|(bool))"));
}

void Parser::parseRawArgs(int typeOfArgs, Command * command){
    if (rawArgs == ""){
        throw NoArguments();
    }
    if(regex_match(rawArgs, argTypes[typeOfArgs])){
        if((typeOfArgs) == 0){
            string temp = rawArgs.substr(1, rawArgs.length() - 2);
            if(!checkTableFieldName(temp)){
                throw StringError();
            }
            command->setTableName(temp);
        }
        else if (typeOfArgs == 1) {
            vector < Data > temp = parseData(rawArgs.substr(1, rawArgs.length() - 2));
            for(Data item : temp) {
                if(!checkTableFieldName(item.fieldName)){
                    throw StringError();
                }
                if(!checkDataType(item.data)){
                    throw typeError(item.data);
                }
            }
            command->setDataToInsert(temp);
        } else if (typeOfArgs == 2) {
            string name, object;
            for (int i = 0; i < rawArgs.length(); ++i) {
                if(rawArgs[i] == ','){
                    name = rawArgs.substr(1, i-2);
                    object = rawArgs.substr(i+1, rawArgs.length() - 1);
                    break;
                }
            }
            if(!checkTableFieldName(name)){
                throw StringError();
            }
            vector < Data > temp = parseData(object.substr(1, object.length() - 2));
            for(Data item : temp) {
                if(!checkTableFieldName(item.fieldName)){
                    throw StringError();
                }
                if(!checkFieldType(item.data)){
                    throw dataTypeError(item.data);
                }
            }
            command->setTableName(name);
            command->setDataToInsert(temp);
        }
        else if (typeOfArgs == 3) {
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
                if(!checkTableFieldName(item.fieldName)){
                    throw StringError();
                }
                if(!checkDataType(item.data)){
                    throw dataTypeError(item.data);
                }
            }


            for(Data item : temp2) {
                if(!checkTableFieldName(item.fieldName)){
                    throw StringError();
                }
                if(!checkDataType(item.data)){
                    throw dataTypeError(item.data);
                }
            }
            command->setDataToFind(temp1);
            command->setDataToInsert(temp2);
        }
    } else {
        throw WrongArgument(typeOfArgs);
    }
}

Command Parser::parse(string input) {
    input = deleteSpacesFromString(input);
    Command result;
    int start = 0, length = 0;
    bool dotFlag = true;
    if (regex_match(input, secondTypeCommand)) {
        result.setCommandType(2);
        for (int i = 0; i < input.length(); i++) {
            if (input[i] == '.' && dotFlag) {
                length = i - start;
                string temp = input.substr(start, length);
                start = i + 1;
                result.setTableName(temp);
                dotFlag = false;
            } else if (input[i] == '(') {
                length = i - start;
                string temp = input.substr(start, length);
                start = i + 1;
                result.setCommand(temp);
            } else if (input[i] == ')') {
                length = i - start;
                string temp = input.substr(start, length);
                setRawArgs(temp);
            }
        }
        checkCommand(&result);
        return result;
    }
    else if (regex_match(input, firstTypeCommand)) {
        result.setCommandType(1);
        for (int i = 0; i < input.length(); i++) {
            if (input[i] == '(') {
                length = i - start;
                string temp = input.substr(start, length);
                start = i + 1;
                result.setCommand(temp);
            }
            else if (input[i] == ')') {
                length = i - start;
                string temp = input.substr(start, length);
                setRawArgs(temp);
            }
        }
        checkCommand(&result);
        return result;
    } else {
        int i = 1, type = 0;
        if(!regex_match(string(1, input[0]), regex("[a-zA-Z]"))) {
            throw wrongSymbolError(input, 0);
        }
        while(i < input.length()){
            if(input[i] == '.' && type == 0){
                type = 2;
            }
            else if(input[i] == '('){
                if(type == 0){
                    type = 1;
                }
                while(i < input.length()){
                    if (input[i] == ')' && i != input.length() - 1){
                        throw wrongSymbolError(input, ++i);
                    }
                    i++;
                }
            } else if (!regex_match(string(1, input[i]), regex("[a-zA-Z0-9]"))) {
                if(i == 0) throw wrongSymbolError(input, i);
            }
            i++;
        }
        throw wrongSymbolError(input, --i);
    }
}