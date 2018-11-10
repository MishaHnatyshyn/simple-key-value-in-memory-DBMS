#include <iostream>
#include <string>
#include <vector>
#include "Parser.h"
using namespace std;

int main() {
    Parser parser;
    string stringTest = "\"key1\":\"value1\", \"key2\":\"value2\", \"key2\":\"value2\"";
    vector<string> result = parser.getKeys(stringTest);
    for (int i = 0; i < result.size(); ++i) {
        cout << result[i] << "   ";
    }

    return 0;
}
