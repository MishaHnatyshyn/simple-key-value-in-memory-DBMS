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

            /*cout << "\n==================== INPUT ====================\n" << endl;
            cout << input << endl;

            cout << "\n==================== PARSED DATA ====================\n" << endl;

            cout << "Command type: "<< to_string(c.getCommandType()) + " | "  << "Table name: " << c.getTableName()+" | " << "command: " << c.getCommand()+" |" << endl;
            vector < Data > tempFindData = c.getDataToFind();
            vector < Data > tempInsertData = c.getDataToInsert();
            cout << "Data to find: " << endl;
            for(Data i : tempFindData){
                cout << "field:\t" << i.fieldName << " data:\t" << i.data << endl;
            }

            cout << "Data to Insert: " << endl;
            for(Data i : tempInsertData){
                cout << "field:\t" << i.fieldName << " data:\t"<< i.data << endl;
            }*/

          cout << "\n==================== OUTPUT ====================\n" << endl;

            db.execute(c);
        }
        catch (ShellError &e){
            e.showError();
        }
        catch (Error &error){
            error.showError();
        }
    }
}

void Shell::displayResult() {

};