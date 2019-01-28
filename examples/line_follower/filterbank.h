#ifndef FILTERBANK_H
#define FILTERBANK_H

#include "IcoFilters.h"

#include <sstream>
#include <iomanip>
#include <string>
#include <fstream>
#include <iostream>
#include <assert.h>


using namespace std;

class filterBank
{
public:
    filterBank();
    ~filterBank();
    void setFilters(int _nfilters);
    void setCoeffFiles(int _index, string _name);
    double doFilterBank(int _filterIndex, double _input);
private:
    int nfilters = 0;
    IcoFilters** filters = NULL;

};

#endif // FILTERBANK_H
