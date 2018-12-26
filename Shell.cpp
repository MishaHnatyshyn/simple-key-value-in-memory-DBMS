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
        if(input == "help"){
            this->displayHelp();
            continue;
        }
        if(input == "info"){
            this->displayInfo();
            continue;
        }
        try {
            Command c = a.parse(input);

            cout << "\n==================== INPUT ====================\n" << endl;
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
            }

            cout << "\n==================== OUTPUT ====================\n" << endl;

            db.execute(c);
        }
        catch (Error &error){
            error.showError();
        }
        catch (...){
        }
    }
}

void Shell::displayHelp() {
    cout << "Welcome in the DBMS Shell!" << endl;
    cout << "" << endl;
    cout << "The Shell commands:" << endl;
    cout << "  exit - stops program" << endl;
    cout << "  help - displays command list" << endl;
    cout << "  info - displays program info" << endl;
    cout << "" << endl;
    cout << "The Table commands:" << endl;
    cout << "  createTable(tableName, {fieldName: type[, fieldName: type]}) - create table" << endl;
    cout << "    example: > createTable(\"exampleTable\", {name: string, age: int})" << endl;

    cout << "  dropTable(tableName) - deletes table" << endl;
    cout << "    example: > dropTable(\"exampleTable\")" << endl;

    cout << "  tables() - show all tables names" << endl;
    cout << "    example: > tables()" << endl;

    cout << "" << endl;
    cout << "Data commands:" << endl;

    cout << "  table.insert({fieldName: value[, fieldName: value]...}) - insert data to table" << endl;
    cout << "    example: > example.insert({age: 19, name: \"Misha\"})" << endl;

    cout << "  table.getOneRow({fieldName: value[, fieldName: value]...}) - displays first founded row" << endl;
    cout << "    example: > example.getOneRow({age: 19, name: \"Misha\"})" << endl;

    cout << "  table.getRows({fieldName: value[, fieldName: value]...}) - displays all founded rows" << endl;
    cout << "    example: > example.getRows({age: 19, name: \"Misha\"})" << endl;

    cout << "  table.deleteRow({fieldName: value[, fieldName: value]...}t) - deletes first founded row" << endl;
    cout << "    example: > example.deleteRow({age: 19, name: \"Misha\"})" << endl;

    cout << "  table.deleteRows({fieldName: value[, fieldName: value]...}) - deletes all founded rows" << endl;
    cout << "    example: > example.deleteRows({age: 19, name: \"Misha\"})" << endl;

    cout << "  table.changeOneRowData({fieldName: value[, fieldName: value]...}, {fieldName: value[, fieldName: value]...}) - changes data for first founded row" << endl;
    cout << "    example: > example.changeOneRowData({age: 19}, {age: 20})" << endl;

    cout << "  table.changeData({fieldName: value[, fieldName: value]...}, {fieldName: value[, fieldName: value]...}) - changes data for all founded rows" << endl;
    cout << "    example: > example.changeData({age: 19}, {age: 20})" << endl;

    cout << "  table.display() - displays all data from table" << endl;
    cout << "    example: > example.display()" << endl;

    cout << "" << endl;
    cout << "For more info you can visit: https://github.com/MishaHnatyshyn/simple-key-value-in-memory-DBMS" << endl;
};

void Shell::displayInfo(){
    cout << "Main information: " << endl;
    cout << "  This program is writen in c++ language and it's an in memory db which can contain key-value pairs" << endl;
    cout << "  Authors: Misha Afnasiuk | Misha Hnatyshyn, students at KPI" << endl;
}