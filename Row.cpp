//
// Created by mhnatyshyn on 06.12.18.
//

#include "Row.h"


Row::Row(vector<Data> data, vector<string> types){
    fieldsCount = data.size();
    for (int i = 0; i < fieldsCount; ++i) {
        fields.push_back(returnProperVal(data[i].data, types[i]));
    }
}

Row::Row(vector<Data> data, vector<string> types, vector<string> fieldNames){
    fieldsCount = fieldNames.size();
    for (int i = 0; i < fieldsCount; ++i) {
        bool flag = false;
        for (int j = 0; j < data.size(); ++j) {
            if (data[j].fieldName == fieldNames[i]) {
                fields.push_back(returnProperVal(data[j].data, types[i]));
                flag = true;
                break;
            }
        }
        if (!flag) fields.push_back(returnDefaultVal(types[i]));
    }
}

CustomType* Row::getElementByIndex(int index){
    return fields[index];
}

CustomType* Row::returnProperVal(string data, string type){
    if (type == "int") return new CustomInt(data);
    if (type == "text") return new CustomString(data.substr(1, data.length()-2));
    if (type == "short") return new CustomShort(data);
    if (type == "float") return new CustomFloat(data);
    if (type == "bool") return new CustomBool(data);
    if (type == "tinytext") return new CustomTinyText(data.substr(1, data.length()-2));
}


CustomType* Row::returnDefaultVal(string type){
    if (type == "int") return new CustomInt();
    if (type == "text") return new CustomString();
    if (type == "short") return new CustomShort();
    if (type == "float") return new CustomFloat();
    if (type == "bool") return new CustomBool();
    if (type == "tinytext") return new CustomTinyText();
}

void Row::display(){
    string res = "";
    for (int i = 0; i < fieldsCount; ++i) {
        res += fields[i]->toString() + "\t";
    }
    cout << res << endl;
}

string Row::toString(){
    string res = "";
    for (int i = 0; i < fieldsCount; ++i) {
        res += fields[i]->toString() + " ";
    }
    return res;
}