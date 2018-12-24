#include <vector>
#include <string>
#include <regex>
#include "TypeError.h"
using namespace std;


class CustomType{
public:
    virtual string toString(){
        cout << "ERR" << endl;
    };

    virtual bool compare(string){}
    virtual void set(string){}
    virtual void validate(string){}
};

class CustomInt: public CustomType{
private:
    int data;
    regex regexInt;
public:


    CustomInt(): data(0){};

    CustomInt(string data){
        regexInt = regex("^[0-9]$");
        validate(data);
        this->data = atoi(data.c_str());
    }
    CustomInt(int data){
        this->data = data;
    }

    virtual string toString(){
        return to_string(data);
    }

    virtual void validate(string data){
//        if (!regex_match(data, this->regexInt)) throw IntError(data);
//        cout << regex_match(data, regex("^[0-9]$")) << endl;
//        if (!regex_match(data, regex("^[0-9]$"))) throw IntError(data);
        if (data == "true" || data == "false") throw IntError(data);
    }

    virtual bool compare(string val){
        validate(val);
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



class CustomFloat: public CustomType{
private:
    float data;
    regex regexFloat;
public:
    CustomFloat(): data(0){};

    CustomFloat(string data){
        regexFloat = regex("^[0-9]+\\.[0-9]+$");
        validate(data);
        this->data = atof(data.c_str());
    }
    CustomFloat(float data){
        this->data = data;
    }
    virtual string toString(){
        return to_string(data);
    }

    virtual bool compare(string val){
        return data == atof(val.c_str());
    }

    virtual void validate(string data){
//        if (!regex_match(data, regexFloat)) throw FloatError(data);
        if (data == "true" || data == "false") throw FloatError(data);
    }

    float get(){
        return data;
    }

    virtual void set(string data){
        this->data = static_cast<float>(atof(data.c_str()));
    }

    virtual void set(int data){
        this->data = data;
    }
};


class CustomShort: public CustomType{
private:
    short data;
    regex regexInt;
public:
    CustomShort(): data(0){}

    CustomShort(string data){
        regexInt = regex("^[0-9]$");
        validate(data);
        this->data = (short) atoi(data.c_str());
    }
    CustomShort(short data){
        this->data = data;
    }

    virtual string toString(){
        return to_string(data);
    }

    virtual bool compare(string val){
        validate(val);
        return data == (short)atoi(val.c_str());
    }

    virtual void validate(string data){
//        if (!regex_match(data, regexInt)) throw ShortError(data, true);
        if (data == "true" || data == "false")  throw ShortError(data, true);
        if (abs(atoi(data.c_str())) > 327677) throw ShortError(data, false);
    }

    short get(){
        return data;
    }

    virtual void set(string data){
        this->data = (short)atoi(data.c_str());
    }

    virtual void set(short data){
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

    CustomString(): data(""){}

    CustomString(string data): data(data){}

    virtual string toString(){
        return data;
    }
    virtual bool compare(string val){
        string newData = val.substr(1, val.length()-2);
        return data == newData;
    }
    virtual void set(string val){
        data = val;
    }
    string get(){
        return data;
    }
};


class CustomTinyText: public CustomType{
private:
    char* data;
public:
    CustomTinyText(){
        this->data = new char[1];
    }

    CustomTinyText(string data){
        validate(data);
        data = new char[data.length()];
        this->data = strdup(data.c_str());
    }
    ~CustomTinyText(){
        delete [] data;
    }
    virtual string toString(){
        return data;
    }
    virtual bool compare(string val){
        validate(val);
        string newData = val.substr(1, val.length()-2);
        return data == newData;
    }
    virtual void validate(string data){
        if (data.length() > 256) throw TinyTextError(data);
    }
    virtual void set(string val){
        data = new char[val.length()];
        data = strdup(val.c_str());
    }
};

class CustomBool: public CustomType{
private:
    bool data;
public:

    CustomBool(): data(false){};

    CustomBool(string data){
        validate(data);
        this->data = data == "true";
    }
    virtual string toString(){
        return data ? "true" : "false";
    }
    virtual bool compare(string val){
        validate(val);
        bool castedVal = (val == "true");
        return data == castedVal;
    }
    virtual void validate(string data){
        if (data != "true" || data != "false") throw BoolError(data);
    }
    virtual void set(string val){
        this->data = (val == "true");
    }
};
