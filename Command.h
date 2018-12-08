#include <iostream>
using namespace std;

class Command {
private:
    int commandType;
    string tableName;
    string command;
    string data;
public:
    int getCommandType();
    void setCommandType(int);
    string getTableName();
    void setTableName(string);
    string getCommand();
    void setCommand(string);
    string getData();
    void setData(string);
};
