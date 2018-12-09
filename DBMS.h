#include "Table.h"

struct TableListNode{
    Table* table;
    string name;
    TableListNode(Table* table,  string name): table(table), name(name){};
};

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
            }
        } else if (commandType == 2){
            if (commandText == "insert"){
                cout<<"START INSERTION"<<endl;
                insert(command.getTableName(), command.getDataToInsert());
                cout<<"DATA INSERTED"<<endl;
            }
            if (commandText == "remove"){
                cout<<"START REMOVING"<<endl;
                remove(command.getTableName(), command.getDataToInsert());
                cout<<"DATA REMOVED"<<endl;
            }
            if (commandText == "display"){
                displayTable(command.getTableName());
            }
        }

    }

    void createTable(string name, vector<Data> fields){
        tables.push_back(new Table(fields, name));
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
        if (fields.size() == 1) {
            currTable->remove(fields[0]);
        } else currTable->remove(fields);
    }

    void displayTable(string name){
        Table* currTable = getTableByName(name);
        currTable->display();
    }

    Table* getTableByName(string name){
        for (int i = 0; i < tables.size(); ++i) {
            if (tables[i]->getName() == name) return tables[i];
        }
        throw WrongTableNameError(name);
    }
};
