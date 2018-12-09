#include "DBMS.h"
#include "ParserError.h"
#include <regex>

class Parser {
private:
    regex firstTypeCommand = regex("[a-zA-Z]*\\(\\\"[a-zA-Z]*\\\"\\)?(,?\\s*\\{([a-zA-Z]*:\\s*((short)|(int)|(float)|(tinytext)|(text)|(bool)),?\\s*)*\\}\\))?");
    regex secondTypeCommand = regex("[a-zA-Z]*\\.[a-zA-Z]*\\(\\{([a-zA-Z]*:\\s*((\\\".*\\\")|([0-9]*\\.?[0-9]*)|true|false),?\\s*)*\\}\\)");
    regex thirdTypeCommand = regex("[a-zA-Z]*\\.[a-zA-Z]*\\(\\{([a-zA-Z]*:\\s*((\\\".*\\\")|([0-9]*\\.?[0-9]*)|true|false),?\\s*)*\\},\\{([a-zA-Z]*:\\s*((\\\".*\\\")|([0-9]*\\.?[0-9]*)|true|false),?\\s*)*\\}\\)");
    regex fourthTypeCommand = regex("[a-zA-Z]*\\.[a-zA-Z]*\\(\\)");
    string deleteSpacesFromString(string);
public:
    Command parse(string);
    vector<Data> parseData(string);
    vector<string>split(string, char symb);
};