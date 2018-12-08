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
    for(string i : Parser::split(data, ',')){
        vector <string > temp = Parser::split(i, ':');
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

Command Parser::parse(string input) {
    input = deleteSpacesFromString(input);
    Command result = Command();
    int start = 0, length = 0;
    if (regex_match(input, secondTypeCommand)) {
        result.setCommandType(2);
        for (int i = 0; i < input.length(); i++) {
            if (input[i] == '.') {
                length = i - start;
                string temp = input.substr(start, length);
                start = i + 1;
                result.setTableName(temp);
            } else if (input[i] == '(') {
                length = i - start;
                string temp = input.substr(start, length);
                start = i + 1;
                result.setCommand(temp);
            } else if (input[i] == '{') {
                start = i+1;
            } else if (input[i] == '}') {
                length = i - start;
                string temp = input.substr(start, length);
                result.setData(parseData(temp));
            }
        }
        return result;
    } else if (regex_match(input, firstTypeCommand)) {
        result.setCommandType(1);
        for (int i = 0; i < input.length(); i++) {
            if (input[i] == '(') {
                length = i - start;
                string temp = input.substr(start, length);
                start = i + 1;
                result.setCommand(temp);
            } else if (input[i] == '"') {
                start = i;
                i++;
                while (input[i] != '"' && i < input.length()) {
                    i++;
                }
                length = i + 1 - start;
                string temp = input.substr(start, length);
                result.setTableName(temp);
            } else if (input[i] == '{') {
                start = i + 1;
            } else if (input[i] == '}') {
                length = i - start;
                string temp = input.substr(start, length);
                result.setData(parseData(temp));
            }
        }
        return result;
    } else {
        int i = 0, type = 0;
        while(i < input.length()){
            if(input[i] == '.'){
                if(i == 0) throw ParserError(input, i);
                type = 2;
            }
            else if(input[i] == '('){
                if(i == 0) throw ParserError(input, i);
                if(type == 0){
                    type = 1;
                }
                i++;
                break;
            }
            else if(!regex_match(string(1, input[i]), regex("[a-zA-Z]"))){
                throw ParserError(input, i);
            }
            i++;
        }
        if(type == 1){
            if(input[i] != '"' ) throw ParserError(input, i);
            i++;
            while(input[i] != '"' && i < input.length()){i++;};
            i++;
            if(input[i] != ',') throw ParserError(input, i);
            i++;
            if(input[i] != '{') throw ParserError(input, i);
            while (input[i] != '}' && i < input.length()){
                while(input[i] != ':' && i < input.length()){
                    if(!regex_match(string(1, input[i]), regex("[a-zA-Z]"))) throw ParserError(input, i);
                    i++;
                }
                i++;
                while(input[i] != ',' && i < input.length()){
                    if(!regex_match(string(1, input[i]), regex("[a-zA-Z]"))) throw ParserError(input, i);
                    i++;
                }
                i++;
            }
            if(input[i] != ')') throw ParserError(input, i);
        } else if (type == 2){
            if(input[i] != '{' ) throw ParserError(input, i);
            i++;
            while (input[i] != '}' && i < input.length()){
                while(input[i] != ':' && i < input.length()){
                    if(!regex_match(string(1, input[i]), regex("[a-zA-Z]"))) throw ParserError(input, i);
                    i++;
                }
                i++;
                while(input[i] != ',' && input[i] != '}' && i < input.length()){
                    if(input[i] == '"'){
                        i++;
                        while(input[i] != '"' && i < input.length()) {
                            i++;
                        }
                        if(input[i] != '"') throw ParserError(input, i);
                    }
                    else if(!regex_match(string(1, input[i]), regex("[0-9,\\.,t,r,u,e,f,a,l,s]"))) throw ParserError(input, i);
                    i++;
                }
                i++;
            }
            if(input[i] != ')') throw ParserError(input, i);
        } else {
            throw ParserError(input, i);
        }
        throw ParserError(input, i);
    }
}