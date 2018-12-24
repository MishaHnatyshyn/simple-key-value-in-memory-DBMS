#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

class ShellError {
public:
  virtual void showError(){
      cout << "Parser Error:" << endl;
  }
};

class ParserError : public ShellError {
private:
    string input;
    int position;
public:
    ParserError(string input, int position):input(input),position(position){};
    virtual void showError(){
        ShellError::showError();
        cout << "Unexpected symbol" << endl;
        cout << input <<  endl;
        cout << setw(position + 1) << "|" << endl;
    };
};

class NoTableName : public ShellError {
public:
    virtual void showError(){
        ShellError::showError();
        cout << "No table name specified" << endl;
    };
};

class UndefinedError : public ShellError {
public:
    virtual void showError(){
        ShellError::showError();
        cout << "Undefined Error" << endl;
    };
};

class NoSuchCommand : public ShellError {
public:
    virtual void showError(){
        ShellError::showError();
        cout << "No such command" << endl;
    };
};

class MustNotHaveArgs : public ShellError {
public:
    virtual void showError(){
        ShellError::showError();
        cout << "This command must not have arguments" << endl;
    };
};

class NoArguments : public ShellError {
public:
    virtual void showError(){
        ShellError::showError();
        cout << "This command must have arguments" << endl;
    };
};

class WrongArgument : public ShellError {
private:
    int typeOfArgs;
    vector < string > argTypesForError = {
            "(\"string\")",
            "(object)",
            "(\"string\", object)",
            "(\"string\", object)",
            "(object, object)"
    };
public:
    WrongArgument(int typeOfArgs):typeOfArgs(typeOfArgs){};
    virtual void showError(){
        ShellError::showError();
        cout << "Wrong argument" << endl;
        cout << "Arguments should be in current format:" << endl;
        cout << argTypesForError[typeOfArgs] << endl;
    };
};

class StringError : public ShellError {
public:
    virtual void showError(){
        ShellError::showError();
        cout << "Table and fields names should contain only letters and numbers and starts only with letters" << endl;
    };
};

class typeError : public ShellError {
private:
    string type;
public:
    typeError(string type):type(type){}
    virtual void showError(){
        ShellError::showError();
        cout << "Unsupported field type: " << type << endl;
    };
};

class dataTypeError : public ShellError {
private:
    string type;
public:
    dataTypeError (string type):type(type){}
    virtual void showError(){
        ShellError::showError();
        cout << "Unsupported data type: " << type << endl;
    };
};