#include "Error.h"

class DBMSError: public Error{
public:
    virtual void showError(){
        cout << "DATA BASE ERROR! " << endl;
    }
};

class WrongTableNameError: public DBMSError{
    string tableName;
public:
    WrongTableNameError(string tableName): tableName(tableName){}
    virtual void showError(){
        cout << "Can not find table with the name " << tableName << endl;
    }
};

class WrongFieldNameError: public DBMSError{
    string tableName;
    string fieldName;
public:
    WrongFieldNameError(string tableName, string fieldName): tableName(tableName), fieldName(fieldName){}
    virtual void showError(){
        cout << "Can not find field with the name " << fieldName << " in the table "<< tableName << endl;
    }
};

class ExistingTableNameError: public DBMSError{
    string tableName;
public:
    ExistingTableNameError(string tableName): tableName(tableName){}
    virtual void showError(){
        cout << "Table with a name " << tableName << " already exists." << endl;
    }
};


class WrongCommand: public DBMSError{
    string command;
public:
    WrongCommand(string command): command(command){}
    virtual void showError(){
        cout << "Wrong command " << command << endl;
    }
};

