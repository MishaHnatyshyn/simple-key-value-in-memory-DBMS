#include <iostream>
#include <iomanip>
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