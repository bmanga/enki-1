#include "IcoFilters.h"

#include <sstream>
#include <iomanip>
#include <string>
#include <fstream>
#include <iostream>
#include <cstring>


using namespace std;

IcoFilters::IcoFilters(){

}

IcoFilters::~IcoFilters(){
     delete [] coefficients;
     delete [] buffer;
}

void IcoFilters::doFIRsetup(string _fileName)
{
    filename=_fileName;

    cout<< "the file name is: " << filename <<endl;
    ifstream infile;
    infile.open(filename);

    if (!infile.is_open()){
        cerr << "Error IcoFilter: " << strerror(errno);
        exit (1);
    }

    /*counting the number of coefficients first so that we can
     * initialise the double pointer to the coefficients according
     * to the number of taps*/
    double count=0;
    nTaps=0;
    while (!infile.eof()){
        infile>>count;
        nTaps++;
    }
    infile.close();
    cout<< "Number of taps are: " << nTaps <<endl;


    coefficients= new double[nTaps];
    buffer= new double[nTaps];

    for (int i=0; i<nTaps; i++){
        buffer[i]=0;
        coefficients[i]=0;
    }

    infile.open(filename);
    for (int i=0; i<nTaps; i++){
        infile>>coefficients[i];
    }
    infile.close();

    cout<< "the 50th coefficient is: " << coefficients[50] <<endl;

    ofstream coefficient;
    coefficient.open("coefficients.txt");
    for (int i=0; i<nTaps; i++){
        coefficient<< coefficients[i]<<"\n";
    }
    coefficient.close();

}

double IcoFilters::doFIRfilter(double _input){
    /* shifting the buffer */
    limit=nTaps-1;
    for (int i=0; i<limit; i++){
        buffer[limit-i]=buffer[limit-1-i];
    }
    buffer[0]=_input;
    double sum=0;
    /* convolution */
    for (int i=0; i<nTaps; i++){
        sum += coefficients[i]*buffer[i];
    }
   // cout<< "IcoFilter is done" << endl;
    return (sum);
}

