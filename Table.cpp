//
// Created by mhnatyshyn on 06.12.18.
//

#include "Table.h"

Table::Table(vector<Data> data, string name): last_index(0), name(name){
    for (int i = 0; i < data.size(); ++i) {
        fields_name.push_back(data[i].fieldName);
        types.push_back(data[i].data);
    }
}

string Table::getName(){
    return name;
}

void Table::display(){
    for (itr = table.begin(); itr != table.end(); ++itr) {
        cout << itr->first << "\t";
        itr->second.display();
    }
}

void Table::update(int id, Data data){
    int fieldIndex = this->getFieldIndex(data.fieldName);
    table.find(id)->second.getElementByIndex(fieldIndex)->set(data.data);
}

void Table::update(int id, vector<Data> options_update){
    vector<int> fieldIndexes;
    fieldIndexes.reserve(options_update.size());
    for (int i = 0; i < options_update.size(); ++i) {
        fieldIndexes.push_back(this->getFieldIndex(options_update[i].fieldName));
    }
    for (int j = 0; j < options_update.size(); ++j) {
        table.find(id)->second.getElementByIndex(fieldIndexes[j])->set(options_update[j].data);
    }
}


void Table::update(Data queryData, Data updateData){
    int fieldIndexFind = this->getFieldIndex(queryData.fieldName);
    int fieldIndex = this->getFieldIndex(updateData.fieldName);
    vector<Row*> query = findManyByOneOption(queryData.fieldName, queryData.data);
    for (int i = 0; i < query.size(); ++i) {
        query[i]->getElementByIndex(fieldIndex)->set(updateData.data);
    }
}

void Table::update(Data queryData, vector<Data> updateData){
    int fieldIndexFind = this->getFieldIndex(queryData.fieldName);
    vector<int> fieldIndexes;
    fieldIndexes.reserve(updateData.size());
    for (int i = 0; i < updateData.size(); ++i) {
        fieldIndexes.push_back(this->getFieldIndex(updateData[i].fieldName));
    }
    vector<Row*> query = findManyByOneOption(queryData.fieldName, queryData.data);
    for (int i = 0; i < query.size(); ++i) {
        for (int j = 0; j < updateData.size(); ++j) {
            query[i]->getElementByIndex(fieldIndexes[j])->set(updateData[j].data);
        }

    }
}

void Table::update(vector<Data> queryData, Data updateData){
    int fieldIndex = this->getFieldIndex(updateData.fieldName);
    vector<Row*> query = findManyBySeveralOptions(queryData);
    for (int i = 0; i < query.size(); ++i) {
        query[i]->getElementByIndex(fieldIndex)->set(updateData.data);
    }
}

void Table::update(vector<Data> queryData, vector<Data> updateData){
    vector<int> fieldIndexes;
    fieldIndexes.reserve(updateData.size());
    for (int i = 0; i < updateData.size(); ++i) {
        fieldIndexes.push_back(this->getFieldIndex(updateData[i].fieldName));
    }
    vector<Row*> query = findManyBySeveralOptions(queryData);
    for (int i = 0; i < query.size(); ++i) {
        for (int j = 0; j < updateData.size(); ++j) {
            query[i]->getElementByIndex(fieldIndexes[j])->set(updateData[j].data);
        }

    }
}

void Table::updateOne(vector<Data> queryData, vector<Data> updateData){
    vector<int> fieldIndexes;
    fieldIndexes.reserve(updateData.size());
    for (int i = 0; i < updateData.size(); ++i) {
        fieldIndexes.push_back(this->getFieldIndex(updateData[i].fieldName));
    }
    Row* query = findOneBySeveralOptions(queryData);
    for (int j = 0; j < updateData.size(); ++j) {
        query->getElementByIndex(fieldIndexes[j])->set(updateData[j].data);
    }
}

void Table::add(Row row){
    last_index++;
    table.insert(pair<int, Row>(last_index, row));
}

void Table::remove(int id){
    this->table.erase(id);
}

void Table::remove(Data data){
    int id = getIndex(data);
    if (id != -1) table.erase(id);
}

void Table::remove(vector<Data> data){
    vector<int> ids = getIndex(data);
    for (int i = 0; i < ids.size(); ++i) {
        if (ids[i] != -1) table.erase(ids[i]);
    }

}

void Table::removeOne(vector<Data> data){
    int id = getIndexOfOne(data);
    if (id != -1) table.erase(id);
}

int Table::getIndex(Data data){
    int fieldIndex = this->getFieldIndex(data.fieldName);
    for (itr = table.begin(); itr != table.end(); ++itr) {
        if (itr->second.getElementByIndex(fieldIndex)->compare(data.data)) {
            return itr->first;
        }
    }
}

int Table::getIndexOfOne(vector<Data> options){
    vector<int> fieldIndexes;
    fieldIndexes.reserve(options.size());
    for (int i = 0; i < options.size(); ++i) {
        fieldIndexes.push_back(this->getFieldIndex(options[i].fieldName));
    }
    for (itr = table.begin(); itr != table.end(); ++itr) {
        bool flag = true;
        for (int i = 0; i < fieldIndexes.size(); ++i) {
            if (!itr->second.getElementByIndex(fieldIndexes[i])->compare(options[i].data)) {
                flag = false;
                break;
            };
        }
        return  itr->first;
    }
}

vector<int> Table::getIndex(vector<Data> options){
    vector<int> result;
    vector<int> fieldIndexes;
    fieldIndexes.reserve(options.size());
    for (int i = 0; i < options.size(); ++i) {
        fieldIndexes.push_back(this->getFieldIndex(options[i].fieldName));
    }
    for (itr = table.begin(); itr != table.end(); ++itr) {
        bool flag = true;
        for (int i = 0; i < fieldIndexes.size(); ++i) {
            if (!itr->second.getElementByIndex(fieldIndexes[i])->compare(options[i].data)) {
                flag = false;
                break;
            };
        }
        if (flag) result.push_back(itr->first);
    }
    return result;
}

int Table::getFieldIndex(string field_name){
    for (int i = 0; i < fields_name.size(); ++i) {
        if (fields_name[i] == field_name) return i;
    }
    throw WrongFieldNameError(name, field_name);
    return -1;
}

void Table::add(vector<Data> data){
    last_index++;
//    table.insert(pair<int, Row>(last_index, Row(data, types)));
    table.insert(pair<int, Row>(last_index, Row(data, types, fields_name)));
}

Row* Table::findById(int id){
    return  &(table.find(id)->second);
}

vector<Row*> Table::findManyByOneOption(string field_name, string value){
    vector<Row*> result;
    int fieldIndex = this->getFieldIndex(field_name);
    for (itr = table.begin(); itr != table.end(); ++itr) {
        if (itr->second.getElementByIndex(fieldIndex)->compare(value)) {
            result.push_back(&(itr->second));
        }
    }
    return result;
}

Row* Table::findOneByOneOption(string field_name, string value){
    int fieldIndex = this->getFieldIndex(field_name);
    for (itr = table.begin(); itr != table.end(); ++itr) {
        if (itr->second.getElementByIndex(fieldIndex)->compare(value)) {
            return &(itr->second);
        }
    }
}

vector<Row*> Table::findManyBySeveralOptions(vector<Data> options){
    vector<Row*> result;
    vector<int> fieldIndexes;
    fieldIndexes.reserve(options.size());
    for (int i = 0; i < options.size(); ++i) {
        fieldIndexes.push_back(this->getFieldIndex(options[i].fieldName));
    }
    for (itr = table.begin(); itr != table.end(); ++itr) {
        bool flag = true;
        for (int i = 0; i < fieldIndexes.size(); ++i) {
            if (!itr->second.getElementByIndex(fieldIndexes[i])->compare(options[i].data)) {
                flag = false;
                break;
            };
        }
        if (flag) result.push_back(&(itr->second));
    }
    return result;
}

Row* Table::findOneBySeveralOptions(vector<Data> options){
    vector<int> fieldIndexes;
    fieldIndexes.reserve(options.size());
    for (int i = 0; i < options.size(); ++i) {
        fieldIndexes.push_back(this->getFieldIndex(options[i].fieldName));
    }
    for (itr = table.begin(); itr != table.end(); ++itr) {
        bool flag = true;
        for (int i = 0; i < fieldIndexes.size(); ++i) {
            cout << itr->second.getElementByIndex(fieldIndexes[i])->toString() << " " << options[i].data << endl;
            if (!itr->second.getElementByIndex(fieldIndexes[i])->compare(options[i].data)) {
                flag = false;
                break;
            };
        }
        if (flag) return &(itr->second);
    }
}

