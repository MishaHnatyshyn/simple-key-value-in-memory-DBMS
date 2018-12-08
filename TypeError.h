#include "Error.h"


class TypeError: public Error{
public:
    virtual void showError(){
        cout << "TYPE ERROR! " << endl;
    }
};

class IntError: public Error{
    string value;
    string field_name;
public:
//    IntError(string value, string field_name): value(value), field_name(field_name){}
    IntError(string value): value(value){}
    virtual void showError(){
//        cout << "Field "<< field_name << "must be type int. Can not convert value "<< value << "to int." << endl;
        cout << "Can not convert value "<< value << " to int." << endl;
    }
};


class ShortError: public Error{
    string value;
    string field_name;
    bool flag;
public:
//    ShortError(string value, string field_name): value(value), field_name(field_name){}
    ShortError(string value, bool flag): value(value), flag(flag){}
    virtual void showError(){
//        cout << "Field "<< field_name << "must be type short. Can not convert value "<< value << " to short." << endl;
        if (flag) cout << "Can not convert value "<< value << " to float." << endl;
        else cout << "Value " << value << " can not fit short type (abs value is larger than 327677)." << endl;
    }
};

class FloatError: public Error{
    string value;
    string field_name;
public:
//    FloatError(string value, string field_name): value(value), field_name(field_name){}
    FloatError(string value): value(value){}
    virtual void showError(){
//        cout << "Field "<< field_name << "must be type float. Can not convert value "<< value << " to float." << endl;
        cout << "Can not convert value "<< value << " to float." << endl;
    }
};

class BoolError: public Error{
    string value;
    string field_name;
public:
//    BoolError(string value, string field_name): value(value), field_name(field_name){}
    BoolError(string value): value(value){}
    virtual void showError(){
//        cout << "Field "<< field_name << "must be type boolean. Can not convert value "<< value << " to boolean." << endl;
        cout << "Can not convert value "<< value << " to boolean. Bool value shoud be 'true' or 'false'." << endl;
    }
};

class TinyTextError: public Error{
    string value;
    string field_name;
public:
//    TinyTextError(string value, string field_name): value(value), field_name(field_name){}
    TinyTextError(string value): value(value){}
    virtual void showError(){
//        cout << "Field "<< field_name << "must be type tiny text (256 char). "<< value << " is longer than 256 char." << endl;
        cout << value << " is longer than 256 char." << endl;
    }
};
