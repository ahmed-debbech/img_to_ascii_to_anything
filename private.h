#ifndef PRIVATE_H
#define PRIVATE_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class PrvFields{

    private:
    string flds[50];

    public:
    PrvFields();
    void print();
    string get(string fld);
};

#endif