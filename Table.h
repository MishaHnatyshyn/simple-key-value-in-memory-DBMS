#include "Row.h"
#include <map>
#include <iterator>


class Table {
private:
    map<int, Row> table;
    vector<string> fields_name;
    vector<string> types;
    int last_index;
    map<int, Row>::iterator itr;
public:
    Table(vector<string> fields_name, vector<string> types): fields_name(fields_name), types(types), last_index(0){}

    void display(){
        for (itr = table.begin(); itr != table.end(); ++itr) {
            itr->second.display();
        }
    }

    void update(int id, string field_name, string value){
        int fieldIndex = this->getFieldIndex(field_name);
        table.find(id)->second.getElementByIndex(fieldIndex)->set(value);
    }

    void update(int id, vector<vector<string>> options_update){
        vector<int> fieldIndexes;
        for (int i = 0; i < options_update.size(); ++i) {
            fieldIndexes.push_back(this->getFieldIndex(options_update[i][0]));
        }
        for (int j = 0; j < options_update.size(); ++j) {
            table.find(id)->second.getElementByIndex(fieldIndexes[j])->set(options_update[j][1]);
        }
    }


    void update(string field_name_find, string value_find, string field_name, string value){
        int fieldIndexFind = this->getFieldIndex(field_name_find);
        int fieldIndex = this->getFieldIndex(field_name);
        vector<Row*> query = findManyByOneOption(field_name_find, value_find);
        for (int i = 0; i < query.size(); ++i) {
            query[i]->getElementByIndex(fieldIndex)->set(value);
        }
    }

    void update(vector<vector<string>> options_find, string field_name, string value){
        int fieldIndex = this->getFieldIndex(field_name);
        vector<Row*> query = findManyBySeveralOptions(options_find);
        for (int i = 0; i < query.size(); ++i) {
            query[i]->getElementByIndex(fieldIndex)->set(value);
        }
    }

    void update(vector<vector<string>> options_find, vector<vector<string>> options_update){
        vector<int> fieldIndexes;
        for (int i = 0; i < options_update.size(); ++i) {
            fieldIndexes.push_back(this->getFieldIndex(options_update[i][0]));
        }
        vector<Row*> query = findManyBySeveralOptions(options_find);
        for (int i = 0; i < query.size(); ++i) {
            for (int j = 0; j < options_update.size(); ++j) {
                query[i]->getElementByIndex(fieldIndexes[j])->set(options_update[j][1]);
            }

        }
    }

    void add(Row row){
        last_index++;
        table.insert(pair<int, Row>(last_index, row));
    }

    void remove(int id){
        this->table.erase(id);
    }

    void remove(string field_name, string value){
        int id = getIndex(field_name, value);
        if (id != -1) table.erase(id);
    }

    int getIndex(string field_name, string value){
        int fieldIndex = this->getFieldIndex(field_name);
        for (itr = table.begin(); itr != table.end(); ++itr) {
            if (itr->second.getElementByIndex(fieldIndex)->compare(value)) {
                return itr->first;
            }
        }
    }

    int getFieldIndex(string field_name){
        for (int i = 0; i < fields_name.size(); ++i) {
            if (fields_name[i] == field_name) return i;
        }
        return -1;
    }

    void add(vector<string> data){
        last_index++;
        table.insert(pair<int, Row>(last_index, Row(data, types)));
    }

    Row* findById(int id){
        return  &(table.find(id)->second);
    }

    vector<Row*> findManyByOneOption(string field_name, string value){
        vector<Row*> result;
        int fieldIndex = this->getFieldIndex(field_name);
        for (itr = table.begin(); itr != table.end(); ++itr) {
            if (itr->second.getElementByIndex(fieldIndex)->compare(value)) {
                result.push_back(&(itr->second));
            }
        }
        return result;
    }

    Row* findOneByOneOption(string field_name, string value){
        int fieldIndex = this->getFieldIndex(field_name);
        for (itr = table.begin(); itr != table.end(); ++itr) {
            if (itr->second.getElementByIndex(fieldIndex)->compare(value)) {
                return &(itr->second);
            }
        }
    }

    vector<Row*> findManyBySeveralOptions(vector<vector<string>> options){
        vector<Row*> result;
        vector<int> fieldIndexes;
        for (int i = 0; i < options.size(); ++i) {
            fieldIndexes.push_back(this->getFieldIndex(options[i][0]));
        }
        for (itr = table.begin(); itr != table.end(); ++itr) {
            bool flag = true;
            for (int i = 0; i < fieldIndexes.size(); ++i) {
                if (!itr->second.getElementByIndex(fieldIndexes[i])->compare(options[i][1])) {
                    flag = false;
                    break;
                };
            }
            if (flag) result.push_back(&(itr->second));
        }
        return result;
    }

    Row* findOneBySeveralOptions(vector<vector<string>> options){
        vector<int> fieldIndexes;
        for (int i = 0; i < options.size(); ++i) {
            fieldIndexes.push_back(this->getFieldIndex(options[i][0]));
        }
        for (itr = table.begin(); itr != table.end(); ++itr) {
            bool flag = true;
            for (int i = 0; i < fieldIndexes.size(); ++i) {
                if (!itr->second.getElementByIndex(fieldIndexes[i])->compare(options[i][1])) {
                    flag = false;
                    break;
                };
            }
            if (flag) return &(itr->second);
        }
    }
};

