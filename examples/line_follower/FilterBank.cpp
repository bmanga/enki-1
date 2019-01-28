#include "FilterBank.h"
#include "Filter.h"


#include <sstream>
#include <iomanip>
#include <string>
#include <fstream>
#include <iostream>
#include <assert.h>


using namespace std;

FilterBank::FilterBank()
{

}

FilterBank::~FilterBank(){
//    for (int i=0; i<nfilters; i++){
//        delete filters[i];
//    }
//    delete[] filters;
}

void FilterBank::setFilters(int _nfilters){
    nfilters=_nfilters;
    filters= new Filter*[nfilters];
    for (int i=0; i<nfilters; i++){
        filters[i]= new Filter();
    }
}

void FilterBank::setCoeffFiles(int _index, string _name){
    assert((_index>=0)&&(_index<nfilters));
    filters[_index]->doFIRsetup(_name);
}

double FilterBank::doFilterBank(int _filterIndex, double _input){
    assert((_filterIndex>=0)&&(_filterIndex<nfilters));
    double output=filters[_filterIndex]->doFIRfilter(_input);
    return (output);
}


