#include "Command.h"
#include <regex>

class Parser {
private:
    regex firstTypeCommand = regex("[a-zA-Z]*\\(\\\"[a-zA-Z]*\\\"(,?\\s*\\{([a-zA-Z]*:\\s*((short)|(int)|(float)|(tinytext)|(text)|(bool)),?\\s*)*\\}\\))?");
    regex secondTypeCommand = regex("[a-zA-Z]*.[a-zA-Z]*\\(\\{([a-zA-Z]*:\\s*((\\\".*\\\")|([0-9]*\\.?[0-9]*)|true|false),?\\s*)*\\}\\)");
    string deleteSpacesFromString(string);
public:
    Command parse(string);
};