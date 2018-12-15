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

    CustomType* getElementByIndex(int);

    CustomType* returnProperVal(string, string);

    void display();

    string toString();
};