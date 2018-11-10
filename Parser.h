#include "iostream"

#include <string>

using namespace std;

#include <vector>
class Parser {

public:
    vector<string> getKeys(string value) {
        vector<string> result;
        vector<string> splitedStirng = split(value, ',');
        for (int i = 0; i < splitedStirng.size(); ++i) {
            int start = 0, length = 0, quotesCounter = 0;
            for (int j = 0; j < splitedStirng[i].length(); ++j) {
                if (splitedStirng[i][j] == '"'){
                    quotesCounter++;
                    if (quotesCounter == 1) start = j;
                    if (quotesCounter == 2) {
                        length = j - start;
                        string temp = splitedStirng[i].substr(start + 1,length - 1);
                        result.push_back(temp);
                        break;
                    }
                }
            }
        }
        return result;
    }

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

};
