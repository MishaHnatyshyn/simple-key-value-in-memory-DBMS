#include <iostream>
#include <string>
#include <vector>
#include "Parser.h"
#include "Table.h"
using namespace std;


int main() {
    vector<string> types = {"int", "string", "string", "int"};
    vector<string> fields_name = {"id", "first_name", "last_name", "age"};
    vector<string> correct_data = {"1", "Misha", "Hnatyshyn", "20"};
    vector<string> wrong_data = {"asdfsaf", "654654", "5.45454", "фівафіва"};

    Table newTable(fields_name, types);

    newTable.add(correct_data);
    newTable.add(wrong_data);

    newTable.display();

    return 0;
}
