#include "Shell.h"

void Shell::start() {
    Parser a = Parser();
    while(1){
        cout << endl << "> ";
        string input;
        getline(cin, input);
        try {

            Command c = a.parse(input);
            cout << c.getCommandType() << " " << c.getTableName() << " " << c.getCommand() << endl;
            vector < Data > temp = c.getData();
            for(Data i : temp){
                cout << "field: " << i.fieldName << " data: " << i.data << endl;
            }
        } catch (ParserError &e){
            e.showError();
        }
    }
}

void Shell::displayResult() {

};