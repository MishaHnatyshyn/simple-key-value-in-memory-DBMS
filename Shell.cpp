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

            cout << "\n==================== INPUT ====================\n" << endl;
            cout << c.getCommandType() << " " << c.getTableName() << " " << c.getCommand() << endl;
            vector < Data > temp = c.getData();

            for(Data i : temp){
                cout << "field: " << i.fieldName << " data: " << i.data << endl;
            }
            cout << "\n==================== INPUT ====================\n" << endl;

            cout << "\n==================== OUTPUT ====================\n" << endl;
            try{
                db.execute(c);
            } catch (Error &error){
                error.showError();
            }
            cout << "\n==================== OUTPUT ====================\n" << endl;
        } catch (ParserError &e){
            e.showError();
        }
    }
}

void Shell::displayResult() {

};