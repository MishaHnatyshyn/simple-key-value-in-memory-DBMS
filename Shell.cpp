#include "Shell.h"


void Shell::start() {
    Parser a = Parser();
    DBMS db;
    while(1){
        cout << endl << "> ";
        string input;
        getline(cin, input);
        try {

            Command c = a.parse(input);

            cout << "==================== INPUT ====================" << endl;
            cout << c.getCommandType() << " " << c.getTableName() << " " << c.getCommand() << endl;
            vector < Data > temp = c.getData();

            for(Data i : temp){
                cout << "field: " << i.fieldName << " data: " << i.data << endl;
            }
            cout << "==================== INPUT ====================" << endl;

            cout << "==================== OUTPUT ====================" << endl;
            db.execute(c);
            cout << "==================== OUTPUT ====================" << endl;
        } catch (ParserError &e){
            e.showError();
        }
    }
}

void Shell::displayResult() {

};