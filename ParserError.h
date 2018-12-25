#include <iostream>
#include <iomanip>
#include <vector>
#include "Error.h"
using namespace std;

class ParserError : public Error {
public:
  virtual void showError(){
      Error::showError();
      cout << "Parser Error:" << endl;
  }
};

class wrongSymbolError : public ParserError {
private:
    string input;
    int position;
public:
    wrongSymbolError(string input, int position):input(input),position(position){};
    virtual void showError(){
        ParserError::showError();
        cout << "Unexpected symbol" << endl;
        cout << input <<  endl;
        cout << setw(position + 1) << "|" << endl;
    };
};

class NoTableName : public ParserError {
public:
    virtual void showError(){
        ParserError::showError();
        cout << "No table name specified" << endl;
    };
};

class UndefinedError : public ParserError {
public:
    virtual void showError(){
        ParserError::showError();
        cout << "Undefined Error" << endl;
    };
};

class NoSuchCommand : public ParserError {
public:
    virtual void showError(){
        ParserError::showError();
        cout << "No such command" << endl;
    };
};

class MustNotHaveArgs : public ParserError {
public:
    virtual void showError(){
        ParserError::showError();
        cout << "This command must not have arguments" << endl;
    };
};

class NoArguments : public ParserError {
public:
    virtual void showError(){
        ParserError::showError();
        cout << "This command must have arguments" << endl;
    };
};

class WrongArgument : public ParserError {
private:
    int typeOfArgs;
    vector < string > argTypesForError = {
            "(\"string\")",
            "(object)",
            "(\"string\", object)",
            "(object, object)"
    };
public:
    WrongArgument(int typeOfArgs):typeOfArgs(typeOfArgs){};
    virtual void showError(){
        ParserError::showError();
        cout << "Wrong argument" << endl;
        cout << "Arguments should be in current format:" << endl;
        cout << argTypesForError[typeOfArgs] << endl;
    };
};

class StringError : public ParserError {
public:
    virtual void showError(){
        ParserError::showError();
        cout << "Table and fields names should contain only letters and numbers and starts only with letters" << endl;
    };
};

class typeError : public ParserError {
private:
    string type;
public:
    typeError(string type):type(type){}
    virtual void showError(){
        ParserError::showError();
        cout << "Unsupported field type: " << type << endl;
    };
};

class dataTypeError : public ParserError {
private:
    string type;
public:
    dataTypeError (string type):type(type){}
    virtual void showError(){
        ParserError::showError();
        cout << "Unsupported data type: " << type << endl;
    };
};