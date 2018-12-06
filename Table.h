#include "Row.h"


class Table {
private:
    vector<Row> table;
    vector<string> fields_name;
    vector<string> types;
public:
    Table(vector<string> fields_name, vector<string> types){
        this->fields_name = fields_name;
        this->types = types;
    }

    void display(){
        for (int i = 0; i < table.size(); ++i) {
            table[i].display();
        }
    }

    void add(Row row){
        table.push_back(row);
    }

    void add(vector<string> data){
        table.push_back(Row(data, types));
    }
};

