#include "filterbank.h"
#include "IcoFilters.h"


#include <sstream>
#include <iomanip>
#include <string>
#include <fstream>
#include <iostream>
#include <assert.h>


using namespace std;

filterBank::filterBank()
{

}

filterBank::~filterBank(){
//    for (int i=0; i<nfilters; i++){
//        delete filters[i];
//    }
//    delete[] filters;
}

void filterBank::setFilters(int _nfilters){
    nfilters=_nfilters;
    filters= new IcoFilters*[nfilters];
    for (int i=0; i<nfilters; i++){
        filters[i]= new IcoFilters();
    }
}

void filterBank::setCoeffFiles(int _index, string _name){
    assert((_index>=0)&&(_index<nfilters));
    filters[_index]->doFIRsetup(_name);
}

double filterBank::doFilterBank(int _filterIndex, double _input){
    assert((_filterIndex>=0)&&(_filterIndex<nfilters));
    double output=filters[_filterIndex]->doFIRfilter(_input);
    return (output);
}


