//
// Created by mhnatyshyn on 08.12.18.
//

#include "DBMS.h"

void DBMS::execute(Command command){
    int commandType = command.getCommandType();
    string commandText = command.getCommand();
    if (commandType == 1){
        if (commandText == "createTable"){
            createTable(command.getTableName(), command.getDataToInsert());
            cout<<"TABLE WAS CREATED" <<endl;
        } else if (commandText == "dropTable"){
            dropTable(command.getTableName());
            cout<<"TABLE WAS DROPPED" <<endl;
        }
        else  if (commandText == "display"){
            displayTable(command.getTableName());
        } else if (commandText == "tables"){
            displayTablesName();
        } else throw WrongCommand(commandText);
    } else if (commandType == 2){
        if (commandText == "insert"){
            insert(command.getTableName(), command.getDataToInsert());
            cout<<"ROW WAS INSERTED" <<endl;
        } else if (commandText == "display"){
            displayTable(command.getTableName());
        } else if (commandText == "getOneRow"){
            findOne(command.getTableName(), command.getDataToInsert());
        } else if (commandText == "getRows"){
            findMany(command.getTableName(), command.getDataToInsert());
        } else if (commandText == "deleteRow"){
            deleteOne(command.getTableName(), command.getDataToInsert());
            cout<<"ROW WAS DELETED" <<endl;
        } else if (commandText == "deleteRows"){
            deleteMany(command.getTableName(), command.getDataToInsert());
            cout<<"ROWS WERE DELETED" <<endl;
        } else if (commandText == "changeOneRowData"){
            updateOne(command.getTableName(), command.getDataToFind(), command.getDataToInsert());
            cout<<"ROW WAS UPDATED" <<endl;
        } else if (commandText == "changeData"){
            updateMany(command.getTableName(), command.getDataToFind(), command.getDataToInsert());
            cout<<"ROWS WERE UPDATED" <<endl;
        } else throw WrongCommand(commandText);
    } else if (commandType == 0){
        if (commandText == "display"){
            displayTable(command.getTableName());
        } else if (commandText == "tables"){
            displayTablesName();
        } else throw WrongCommand(commandText);
    }
}

void DBMS::createTable(string name, vector<Data> fields){
    for (int i = 0; i < tables.size(); ++i) {
        if (tables[i]->getName() == name) throw ExistingTableNameError(name);
    }
    tables.push_back(new Table(fields, name));
}

void DBMS::dropTable(string name){
    int index = -1;
    for (int i = 0; i < tables.size(); ++i) {
        if (tables[i]->getName() == name) {
            index = i;
            break;
        }
    }
    if (index == -1 ) throw WrongTableNameError(name);
    tables.erase(tables.begin() + index);
}

void DBMS::displayTablesName(){
    for (int i = 0; i < tables.size(); ++i) {
        cout << tables[i]->getName() << endl;
    }
}

void DBMS::insert(string name, vector<Data> fields){
    Table* currTable = getTableByName(name);
    currTable->add(fields);
}

void DBMS::remove(string name, vector<Data> fields){
    Table* currTable = getTableByName(name);
    currTable->remove(fields);
}

void DBMS::displayTable(string name){
    Table* currTable = getTableByName(name);
    currTable->display();
}

void DBMS::findOne(string name, vector<Data> fields){
    Table* currTable = getTableByName(name);
    currTable->findOneBySeveralOptions(fields)->display();
}

void DBMS::updateOne(string name, vector<Data> fieldsFind, vector<Data> fieldsUpdate){
    Table* currTable = getTableByName(name);
    currTable->updateOne(fieldsFind, fieldsUpdate);
}

void DBMS::updateMany(string name, vector<Data> fieldsFind, vector<Data> fieldsUpdate){
    Table* currTable = getTableByName(name);
    currTable->update(fieldsFind, fieldsUpdate);
}

void DBMS::deleteOne(string name, vector<Data> fields){
    Table* currTable = getTableByName(name);
    currTable->removeOne(fields);
}

void DBMS::deleteMany(string name, vector<Data> fields){
    Table* currTable = getTableByName(name);
    currTable->remove(fields);
}

void DBMS::findMany(string name, vector<Data> fields){
    Table* currTable = getTableByName(name);
    vector<Row*> result = currTable->findManyBySeveralOptions(fields);
    for (int i = 0; i < result.size(); ++i) {
        result[i]->display();
    }
}

Table* DBMS::getTableByName(string name){
    for (int i = 0; i < tables.size(); ++i) {
        if (tables[i]->getName() == name) return tables[i];
    }
    throw WrongTableNameError(name);
}
