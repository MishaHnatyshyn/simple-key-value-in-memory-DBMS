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
    void execute(Command);

    void createTable(string, vector<Data>);

    void dropTable(string);

    void displayTablesName();

    void insert(string, vector<Data>);

    void remove(string, vector<Data>);

    void displayTable(string);

    void findOne(string, vector<Data>);

    void updateOne(string, vector<Data>, vector<Data>);

    void updateMany(string, vector<Data>, vector<Data>);

    void deleteOne(string, vector<Data>);

    void deleteMany(string, vector<Data>);

    void findMany(string, vector<Data>);

    Table* getTableByName(string);
};
