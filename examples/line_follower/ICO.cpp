#include "ICO.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


using namespace std;

Ico::Ico(int _nInputs)
{
    nInputs=_nInputs;
    /* this is the number of filters used to filter each
     * predictor signal */

    inputs=new double[nInputs];
    weights= new double[nInputs];
    for (int i=0; i<nInputs; i++){
        weights[i]=1;
        weights++;
    }

    //saving initial weights
    initialWeights= new double[nInputs];
    for (int i=0; i<nInputs; i++){
        initialWeights[i]=weights[i];
        weights++;
        initialWeights++;
    }
}

Ico::~Ico(){
    delete [] inputs;
    delete [] weights;
    delete [] initialWeights;
}

void Ico::setInput(double* _predictors) {
    for (int i=0; i<nInputs; i++){
        inputs[i]=_predictors[i];
    }
}

void Ico::setError(double _error){
    error=_error;
}

void Ico::setErrorDerivative(double _error){

    //if use derivative:
    curr_error=_error;
    error=(prev_error-curr_error)/2;
    prev_error=curr_error;

}

void Ico::setLearningFactor(double _learningRate){
    learningRate=_learningRate;
}

void Ico::updateWeights(){
    for (int i=0; i<nInputs; i++){
        weights[i] += learningRate * error * inputs[i];
    }
}

double Ico::getWeightsDistance(){
    weightChange=0;
    double weightsDifference =0;
    for (int i=0; i<nInputs; i++){
        weightsDifference = weights[i] - initialWeights[i];
        weightChange += weightsDifference*weightsDifference;
    }
    return (sqrt(weightChange));
}

double Ico::getWeight(int _index){
    assert((_index>=0)&&(_index<nInputs));
    return (weights[_index]);
}

void Ico::doSum(){
    sum=0;
    for (int k=0; k<nInputs; k++){
        sum+=inputs[k] * weights[k];
    }
}

double Ico::getOutput(){
    return (sum);
}





