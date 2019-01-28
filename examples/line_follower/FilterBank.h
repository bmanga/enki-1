#pragma once

#include "Filter.h"

#include <sstream>
#include <iomanip>
#include <string>
#include <fstream>
#include <iostream>
#include <assert.h>


using namespace std;

class FilterBank
{
public:
    FilterBank();
    ~FilterBank();
    void setFilters(int _nfilters);
    void setCoeffFiles(int _index, string _name);
    double doFilterBank(int _filterIndex, double _input);
private:
    int nfilters = 0;
    Filter** filters = NULL;

};
