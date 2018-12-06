#include "Parser.h"

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
                start = i;
            } else if (input[i] == '}') {
                length = i + 1 - start;
                string temp = input.substr(start, length);
                result.setData(temp);
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
                start = i;
            } else if (input[i] == '}') {
                length = i + 1 - start;
                string temp = input.substr(start, length);
                result.setData(temp);
            }
        }
        return result;
    } else {
        cout << "error";
        cout << input;
    }
}