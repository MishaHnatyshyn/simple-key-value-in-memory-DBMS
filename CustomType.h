#include <vector>
#include <string>
#include <regex>

using namespace std;


class CustomType{
public:
    virtual string toString(){
        cout << "ERR" << endl;
    };

    virtual bool compare(string){}
    virtual void set(string){}
};

class CustomInt: public CustomType{
private:
    int data;
public:
    CustomInt(string data){
        regex regexInt("^[0-9]$");
//        if (!regex_match(data, regexInt)) cout << "TYPE ERROR  " << data << endl;
        this->data = atoi(data.c_str());
    }
    CustomInt(int data){
        this->data = data;
    }
    virtual string toString(){
        return to_string(data);
    }

    virtual bool compare(string val){
        return data == atoi(val.c_str());
    }

    int get(){
        return data;
    }

    virtual void set(string data){
        this->data = atoi(data.c_str());
    }

    virtual void set(int data){
        this->data = data;
    }
};

class CustomIntArray: public CustomType{
private:
    vector<int> data;
public:
    CustomIntArray(vector<string> data){
        this->data = vector<int>(data.size());
        for (int i = 0; i < data.size(); ++i) {
            this->data[i] = atoi(data[i].c_str());
        }
    };
    virtual string toString(){
        string res = "[ ";
        for (int i = 0; i < data.size(); ++i) {
            res += to_string(data[i]);
            if (i != data.size() - 1 ) res += ", ";
        }
        res += " ]";
        return res;
    }
};

class CustomString: public CustomType{
private:
    string data;
public:
    CustomString(string data): data(data){}
    virtual string toString(){
        return data;
    }
    virtual bool compare(string val){
        return data == val;
    }
    virtual void set(string val){
        data = val;
    }
};


