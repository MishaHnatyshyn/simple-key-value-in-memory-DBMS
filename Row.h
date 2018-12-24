#include <iostream>
#include "CustomType.h"
#include "Command.h"

using namespace std;


class Row{
private:
    vector<CustomType*> fields;
    int fieldsCount;
public:
    Row(vector<Data>, vector<string>);

    Row(vector<Data>, vector<string>, vector<string>);

    CustomType* getElementByIndex(int);

    CustomType* returnProperVal(string, string);

    CustomType* returnDefaultVal(string);

    void display();

    string toString();
};