#include <iostream>
#include <vector>
//#include "DBMS.h"
using namespace std;

struct Data{
    string fieldName;
    string data;
    Data(string fieldName, string data): fieldName(fieldName), data(data){}
};

class Command {
private:
    int commandType;
    string tableName;
    string command;
    vector < Data > dataToFind;
    vector < Data > dataToInsert;
public:
    int getCommandType();
    void setCommandType(int);
    string getTableName();
    void setTableName(string);
    string getCommand();
    void setCommand(string);
    vector < Data >  getDataToFind();
    vector < Data >  getDataToInsert();
    void setDataToFind(vector< Data >);
    void setDataToInsert(vector< Data >);
};
