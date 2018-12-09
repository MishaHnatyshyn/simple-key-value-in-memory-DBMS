#include <iostream>
#include "CustomType.h"
#include "Command.h"

using namespace std;


class Row{
private:
    vector<CustomType*> fields;
    int fieldsCount;
public:
    Row(vector<Data> data, vector<string> types){
        fieldsCount = data.size();
        for (int i = 0; i < fieldsCount; ++i) {
            fields.push_back(returnProperVal(data[i].data, types[i]));
        }
    }

    CustomType* getElementByIndex(int index){
        return fields[index];
    }

    CustomType* returnProperVal(string data, string type){
        if (type == "int") return new CustomInt(data);
        if (type == "text") return new CustomString(data.substr(1, data.length()-2));
        if (type == "short") return new CustomShort(data);
        if (type == "float") return new CustomFloat(data);
        if (type == "bool") return new CustomBool(data);
        if (type == "tinytext") return new CustomTinyText(data.substr(1, data.length()-2));

    }

    void display(){
        string res = "";
        for (int i = 0; i < fieldsCount; ++i) {
            res += fields[i]->toString() + "\t";
        }
        cout << res << endl;
    }

    string toString(){
        string res = "";
        for (int i = 0; i < fieldsCount; ++i) {
            res += fields[i]->toString() + " ";
        }
        return res;
    }
};