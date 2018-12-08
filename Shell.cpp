#include "Shell.h"

void Shell::start() {
    while(1){
        cout << endl << "> ";
        string input;
        getline(cin, input);
        Parser a = Parser();
        Command c = a.parse(input);
        cout << c.getCommandType() << " " << c.getTableName() << " " << c.getCommand() << " " << c.getData();
    }
}

void Shell::displayResult() {

};