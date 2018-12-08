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



class CustomFloat: public CustomType{
private:
    float data;
public:
    CustomFloat(string data){
        regex regexInt("^[0-9]$");
//        if (!regex_match(data, regexInt)) cout << "TYPE ERROR  " << data << endl;
        this->data = static_cast<float>(atof(data.c_str()));
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
public:
    CustomShort(string data){
        regex regexInt("^[0-9]$");
//        if (!regex_match(data, regexInt)) cout << "TYPE ERROR  " << data << endl;
        this->data = (short) atoi(data.c_str());
    }
    CustomShort(short data){
        this->data = data;
    }

    virtual string toString(){
        return to_string(data);
    }

    virtual bool compare(string val){
        return data == (short)atoi(val.c_str());
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


class CustomTinyText: public CustomType{
private:
    char* data;
public:
    CustomTinyText(string data){
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
        return data == val;
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
    CustomBool(string data){
        this->data = data == "true";
    }
    virtual string toString(){
        return data ? "true" : "false";
    }
    virtual bool compare(string val){
        bool castedVal = (val == "true");
        return data == castedVal;
    }
    virtual void set(string val){
        this->data = (val == "true");
    }
};
