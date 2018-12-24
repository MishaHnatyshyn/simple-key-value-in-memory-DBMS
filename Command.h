#include <iostream>
#include <vector>
#include <regex>

#include "ParserError.h"
using namespace std;

struct Data{
    string fieldName;
    string data;
    Data(string fieldName, string data): fieldName(fieldName), data(data){}
};

class Command {
private:
    int commandType;
    string tableName = "";
    string command = "";
    string rawArgs = "";
    vector < Data > dataToFind;
    vector < Data > dataToInsert;
    vector < regex > argTypes {
        regex("\\\".*\\\""),
        regex("\\{.*\\:.*(,.*\\:.*)*?\\}"),
        regex("\\{.*\\:.*(\\,.*\\:.*)*?\\},\\{.*\\:.*(\\,.*\\:.*)*?\\}"),
        regex("\\\".*\\\"\\,\\{.*\\:.*(\\,.*\\:.*)*?\\}"),
        regex("\\{.*\\:.*(\\,.*\\:.*)*?\\},\\{.*\\:.*(\\,.*\\:.*)*?\\}")
    };
    vector<string> split(string str,char symb){
        vector<string> result;
        int start = 0 , length = 0;
        for (int i = 0; i <= str.length(); ++i) {
            if (str[i] == symb || i == str.length()){
                length = i - start;
                string temp = str.substr(start,length);
                start +=length + 1;
                result.push_back(temp);
            }
        }
        return result;
    }
    vector<Data>parseData(string data) {
        vector<Data> result;
        for(string i : split(data, ',')){
            vector <string > temp = split(i, ':');
            result.push_back(Data(temp[0], temp[1]));
        }
        return result;
    }
public:
    void parseRawArgs(int);
    int getCommandType();
    void setCommandType(int);
    string getTableName();
    void setTableName(string);
    string getCommand();
    void setRawArgs(string);
    string getRawArgs();
    void setCommand(string);
    vector < Data >  getDataToFind();
    vector < Data >  getDataToInsert();
    void setDataToFind(vector< Data >);
    void setDataToInsert(vector< Data >);
};
