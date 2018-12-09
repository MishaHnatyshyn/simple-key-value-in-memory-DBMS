#include "Shell.h"


void Shell::start() {
    Parser a = Parser();
    DBMS db;
    while(1){
        cout << endl << "> ";
        string input;
        getline(cin, input);
        if(input == "exit"){
            break;
        }
        try {
            Command c = a.parse(input);

//            cout << "\n==================== INPUT ====================\n" << endl;
//            cout << c.getCommandType() << " " << c.getTableName() << " " << c.getCommand() << endl;
            vector < Data > tempFindData = c.getDataToFind();
            vector < Data > tempInsertData = c.getDataToInsert();
//            cout << "Data to find: " << endl;
//            for(Data i : tempFindData){
//                cout << "field: " << i.fieldName << " data: " << i.data << endl;
//            }

//            cout << "Data to Insert: " << endl;
//            for(Data i : tempInsertData){
//                cout << "field: " << i.fieldName << " data: " << i.data << endl;
//            }
//            cout << "\n==================== INPUT ====================\n" << endl;

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