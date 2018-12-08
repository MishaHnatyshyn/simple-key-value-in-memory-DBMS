#include <iostream>
#pragma once
using namespace std;

class Error {
public:
    virtual void showError(){
        cout << "ERROR! " << endl;
    }
};

