#include <iostream>
#include "CustomType.h"
#include "Command.h"

using namespace std;


class Row{
private:
    vector<CustomType*> fields;
    int count;
public:
    Row(vector<CustomType*> fields): fields(fields){}

    Row(vector<string> data, vector<string> types){
        for (int i = 0; i < data.size(); ++i) {
            fields.push_back(returnProperVal(data[i], types[i]));
        }
    }

    Row(vector<Data> data, vector<string> types){
        for (int i = 0; i < data.size(); ++i) {
            fields.push_back(returnProperVal(data[i].data, types[i]));
        }
    }

    CustomType* getElementByIndex(int index){
        return fields[index];
    }

    CustomType* returnProperVal(string data, string type){
        if (type == "int") return new CustomInt(data);
        if (type == "text") return new CustomString(data);
        if (type == "short") return new CustomShort(data);
        if (type == "float") return new CustomFloat(data);
        if (type == "bool") return new CustomBool(data);

    }

    void display(){
//        cout << "ROW DISPLAY" << endl;
        string res = "";
        for (int i = 0; i < fields.size(); ++i) {
            res += fields[i]->toString() + "\t";
        }
        cout << res << endl;
    }

    string toString(){
        string res = "";
        for (int i = 0; i < fields.size(); ++i) {
            res += fields[i]->toString() + " ";
        }
        return res;
    }
};