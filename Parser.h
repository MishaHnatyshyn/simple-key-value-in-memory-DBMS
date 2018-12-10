#include "commandChecker.h"
#include <regex>

class Parser {
private:
    regex firstTypeCommand = regex("^[a-zA-Z][a-zA-Z0-9]*\\(.*\\)");
    regex secondTypeCommand = regex("[a-zA-Z][a-zA-Z0-9]*\\.[a-zA-Z][a-zA-Z0-9]*\\(.*\\)");
    string deleteSpacesFromString(string);
public:
    Command parse(string);
    vector<Data> parseData(string);
    vector<string>split(string, char symb);
};