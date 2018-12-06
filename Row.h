#include <iostream>
#include "CustomType.h"

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

    CustomType* returnProperVal(string data, string type){
        if (type == "int") return new CustomInt(data);
        if (type == "string") return new CustomString(data);

    }

    void display(){
        cout << "ROW DISPLAY" << endl;
        string res = "";
        for (int i = 0; i < fields.size(); ++i) {
            res += fields[i]->toString() + " ";
        }
        cout << res << endl;
    }
};