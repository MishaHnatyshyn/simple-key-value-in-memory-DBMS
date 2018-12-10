#include "Table.h"

/*
 createTable("User", {name: text, age:int})
 User.insert({name:"Misha", age: 19})
 User.insert({name:"Bogdan", age: 18})
 User.insert({name:"Oleg", age: 21})
*/


class DBMS {
private:
    vector<Table*> tables;
public:
    void execute(Command command){
        int commandType = command.getCommandType();
        string commandText = command.getCommand();
        if (commandType == 1){
            if (commandText == "createTable"){
                createTable(command.getTableName(), command.getDataToInsert());
                cout<<"TABLE CREATED" <<endl;
            } else if (commandText == "dropTable"){
                dropTable(command.getTableName());
                cout<<"TABLE DROPPED" <<endl;
            }
            else  if (commandText == "display"){
                displayTable(command.getTableName());
            } else if (commandText == "tables"){
                displayTablesName();
            } else throw WrongCommand(commandText);
        } else if (commandType == 2){
            if (commandText == "insert"){
                insert(command.getTableName(), command.getDataToInsert());
            } else if (commandText == "display"){
                displayTable(command.getTableName());
            } else if (commandText == "getOneRow"){
                findOne(command.getTableName(), command.getDataToInsert());
            } else if (commandText == "getRows"){
                findMany(command.getTableName(), command.getDataToInsert());
            } else if (commandText == "deleteRow"){
                deleteOne(command.getTableName(), command.getDataToInsert());
            } else if (commandText == "deleteRows"){
                deleteMany(command.getTableName(), command.getDataToInsert());
            } else if (commandText == "changeOneRowData"){
                updateOne(command.getTableName(), command.getDataToFind(), command.getDataToInsert());
            } else if (commandText == "changeData"){
                updateMany(command.getTableName(), command.getDataToFind(), command.getDataToInsert());
            } else throw WrongCommand(commandText);
        } else if (commandType == 0){
            if (commandText == "display"){
                displayTable(command.getTableName());
            } else if (commandText == "tables"){
                displayTablesName();
            } else throw WrongCommand(commandText);
        }
    }

    void createTable(string name, vector<Data> fields){
        for (int i = 0; i < tables.size(); ++i) {
            if (tables[i]->getName() == name) throw ExistingTableNameError(name);
        }
        tables.push_back(new Table(fields, name));
    }

    void dropTable(string name){
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

    void displayTablesName(){
        for (int i = 0; i < tables.size(); ++i) {
            cout << tables[i]->getName() << endl;
        }
    }

    void insert(string name, vector<Data> fields){
        Table* currTable = getTableByName(name);
        currTable->add(fields);
    }

    void remove(string name, vector<Data> fields){
        Table* currTable = getTableByName(name);
        currTable->remove(fields);
    }

    void displayTable(string name){
        Table* currTable = getTableByName(name);
        currTable->display();
    }

    void findOne(string name, vector<Data> fields){
        Table* currTable = getTableByName(name);
        currTable->findOneBySeveralOptions(fields)->display();
    }

    void updateOne(string name, vector<Data> fieldsFind, vector<Data> fieldsUpdate){
        Table* currTable = getTableByName(name);
        currTable->updateOne(fieldsFind, fieldsUpdate);
    }

    void updateMany(string name, vector<Data> fieldsFind, vector<Data> fieldsUpdate){
        Table* currTable = getTableByName(name);
        currTable->update(fieldsFind, fieldsUpdate);
    }

    void deleteOne(string name, vector<Data> fields){
        Table* currTable = getTableByName(name);
        currTable->removeOne(fields);
    }

    void deleteMany(string name, vector<Data> fields){
        Table* currTable = getTableByName(name);
        currTable->remove(fields);
    }

    void findMany(string name, vector<Data> fields){
        Table* currTable = getTableByName(name);
        vector<Row*> result = currTable->findManyBySeveralOptions(fields);
        for (int i = 0; i < result.size(); ++i) {
            result[i]->display();
        }
    }

    Table* getTableByName(string name){
        for (int i = 0; i < tables.size(); ++i) {
            if (tables[i]->getName() == name) return tables[i];
        }
        throw WrongTableNameError(name);
    }
};
