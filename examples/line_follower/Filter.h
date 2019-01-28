#pragma once

#include <sstream>
#include <iomanip>
#include <string>
#include <fstream>
#include <iostream>


using namespace std;


class Filter
{
public:
    Filter();
    ~Filter();
    void doFIRsetup(string _fileName);
    double doFIRfilter(double _input);

private:

    string filename;
    double* coefficients=0;
    int nTaps=0;
    int limit=0;
    double* buffer=0;
};
