#pragma once

#include <iostream>
#include<math.h>
#include<stdio.h>

using namespace std;


class Ico
{
public:
    Ico(int _nInputs);
    ~Ico();
    void setInput(double* _predictors);
    void setError(double _error);
    void setErrorDerivative(double _error);
    void setLearningFactor(double _learningFactor);
    void updateWeights();
    double getWeightsDistance();
    void doSum();
    double getOutput();
    double getWeight(int _index);

private:
    int nInputs=0;
    double* inputs=0;
    double* weights=0;
    double* initialWeights=0;
    double weightChange=0;
    double weightDistance=0;
    double error=0;
    double curr_error=0;
    double prev_error=0;
    double learningRate=0;
    double sum=0;

};
