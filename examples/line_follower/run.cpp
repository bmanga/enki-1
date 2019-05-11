/*
    Enki - a fast 2D robot simulator
    Copyright (C) 2017 Bernd Porr <mail@berndporr.me.uk>
    Copyright (C) 1999-2016 Stephane Magnenat <stephane at magnenat dot net>
    Copyright (C) 2004-2005 Markus Waibel <markus dot waibel at epfl dot ch>
    Copyright (c) 2004-2005 Antoine Beyeler <abeyeler at ab-ware dot com>
    Copyright (C) 2005-2006 Laboratory of Intelligent Systems, EPFL, Lausanne
    Copyright (C) 2006-2008 Laboratory of Robotics Systems, EPFL, Lausanne
    See AUTHORS for details

    This program is free software; the authors of any publication 
    arising from research using this software are asked to add the 
    following reference:
    Enki - a fast 2D robot simulator
    http://home.gna.org/enki
    Stephane Magnenat <stephane at magnenat dot net>,
    Markus Waibel <markus dot waibel at epfl dot ch>
    Laboratory of Intelligent Systems, EPFL, Lausanne.

    You can redistribute this program and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/*
Custom Robot example which has ground sensors and follows a line
It has also a camera which looks to the front and IR sensors
*/

#include <../../enki/Enki.h>
#include <QApplication>
#include <QtGui>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <sstream>
#include <iomanip>

#include "Racer.h"
#include "Ico.h"
#include "clbp/Neuron.h"
#include "clbp/Layer.h"
#include "clbp/Net.h"
#include "../lib/Net.cpp"
#include "../lib/Layer.cpp"
#include "../lib/Neuron.cpp"
#include "filterbank.h"
#include "IcoFilters.h"


#define reflex //use reflex or icoLearner or bpLearner
#ifdef icoLearner
        #define PredDiff //or not defined
        #define doFilter
#endif
#ifdef bpLearner
        #define filterBnk
        #define PredDiff
#endif
//#define doFilter //or do filterBank or nofilter
//#define noFilter
//#define filterBnk
//#define PredBinary
//#define PredDelay
//#define errorBinary

//#define positionMode

using namespace Enki;
using namespace std;

double	maxx = 300;
double	maxy = 300;

int line=0;
int iterateCount=0;
int delay=0;

int nPredictors=6; //this cannot be an odd number for icoLearner
#ifdef PredDiff
int nInputs=nPredictors/2;
#endif
#ifndef PredDiff
int nInputs=nPredictors;
#endif
#ifdef filterBnk
int nFilters = 2;
#endif

class EnkiPlayground : public EnkiWidget
{
protected:
	Racer* racer;
    double speed = 90;
    double prevX;
    double prevY;
    double prevA;
#ifdef icoLearner
    Ico* ico;
#endif
#ifdef bpLearner
    Net* net;
#endif
#ifdef doFilter
    IcoFilters** icoFilter = 0;
#endif
#ifdef filterBnk
    filterBank** filterBanks= 0;
#endif
    FILE* flog = NULL;
    FILE* errorlog = NULL;
    FILE* fcoord = NULL;
public:
    EnkiPlayground(World *world, QWidget *parent = 0):
		EnkiWidget(world, parent)
	{
        flog = fopen("flog.tsv","wt");
        fcoord = fopen("coord.tsv","wt");
        errorlog=fopen("error.txt","wt");
        racer = new Racer;
        racer->pos = Point(maxx/2, maxy/2); // x and y of the start point
		racer->leftSpeed = speed;
		racer->rightSpeed = speed;
        world->addObject(racer);
#ifdef filterBnk
        filterBanks = new filterBank*[nInputs];
        string filenames[nFilters] = {"h.dat", "hh.dat"};
        for (int i=0; i<nInputs; i++){
            filterBanks[i]= new filterBank();
            filterBanks[i]->setFilters(nFilters);
            for (int j=0; j<nFilters; j++){
                filterBanks[i]->setCoeffFiles(j, filenames[j]);
            }
        }
        nInputs = nInputs * nFilters;
#endif
#ifdef icoLearner
        ico= new Ico(nInputs);
#endif
#ifdef bpLearner
        int nLayers=4;
        int nNeurons[nLayers]={12,6,3,1};
        int* nNeuronsp=nNeurons;
        net = new Net(nLayers, nNeuronsp, nInputs);
        net->initWeights(Neuron::W_RANDOM, Neuron::B_NONE);
#endif
#ifdef doFilter
        string filename = "h.dat";

        icoFilter= new IcoFilters*[nInputs];
        for (int i=0; i<nInputs; i++){
            icoFilter[i]= new IcoFilters();
            icoFilter[i]->doFIRsetup(filename);
        }
#endif
#ifdef filterBnk
        nInputs = nInputs / nFilters;
#endif
        std::ofstream myfilestat;
        myfilestat.open ("stat.txt", fstream::app);
        myfilestat << nInputs << "\n";
#ifdef bpLearner
        for (int i=0; i<nLayers; i++){
            myfilestat << nNeurons[i] << "\n";
        }
#endif
        myfilestat.close();
	}

    ~EnkiPlayground(){
        fclose(flog);
        fclose(fcoord);
        fclose(errorlog);
    }

	// here we do all the behavioural computations
	// as an example: line following and obstacle avoidance
	virtual void sceneCompletedHook()
	{

//        iterateCount=iterateCount+1;
//        if (iterateCount==500){
//            racer->pos = Point(0,-60); // x and y of the start point
//            iterateCount=0;
//        }

#ifdef bpLearner
        int errorGain=1;
        int predGain=1;
#endif
#ifdef icoLearner
        int errorGain=1;
        int predGain=1;
#endif

#ifdef reflex
        int errorGain=1;
        int predGain=1;
#endif
		double leftGround = racer->groundSensorLeft.getValue();
		double rightGround = racer->groundSensorRight.getValue();
        double error = errorGain * (leftGround - rightGround);
       // fprintf(stderr,"program: the error value: %f\n", error);

        fprintf(fcoord,"%e\t%e\n",racer->pos.x,racer->pos.y);
        fprintf(errorlog, "%e\n", error);
         //fprintf(errorlog, "%e\t%e\n", leftGround, rightGround);

#ifdef reflex
        int gain=300;
        speed=80;

        racer->leftSpeed  = speed + error * gain;
        racer->rightSpeed = speed - error * gain;
#endif
#ifndef reflex
        //predictor sensors:
        double pred[nPredictors]; // exception

        pred[4] = racer->groundSensorFrontP0.getValue();
        pred[0] = racer->groundSensorFrontP1.getValue();
        pred[2] = racer->groundSensorFrontP2.getValue();
//        pred[2] = racer->groundSensorFrontP3.getValue();
        pred[3] = racer->groundSensorFrontP4.getValue();
        pred[1] = racer->groundSensorFrontP5.getValue();
        pred[5] = racer->groundSensorFrontP6.getValue();

#ifdef PredBinary
        for (int i=0; i<nPredictors; i++){
            if (pred[i]<0.70){
                pred[i]=-0.1 * predGain;
            }
            else{
                pred[i]=0;
            }
        }
#endif

#ifdef PredDiff
        /* using the difference of the two predictors as the input: */
        for (int i=0; i<nInputs; i++){
            pred[i]=1 * (pred[2 * i]-pred[2 * i+1]); //the numbering of the predictors becomes important
            cout<< "**********" <<pred[i]<<endl;
        }
#endif

#ifdef positionMode
        cout << ">>>>>>>>>>>>>>" << racer->groundSensorFrontP1.getAbsolutePosition() << endl;
#endif

#ifdef doFilter
        double pred_filtered[nInputs];
        for (int i=0; i<nInputs; i++){
            pred_filtered[i]=icoFilter[i]->doFIRfilter(pred[i]);
            cout<<"FILTER "<<i<<endl;
            fprintf(stderr,"program: the Pred value: %f\n", pred[i]);
            fprintf(stderr,"program: the Filtered value: %f\n", pred_filtered[i]);
        }

        double* pred_pointer=pred_filtered;
#endif

#ifdef filterBnk
        double pred_filtered[nInputs][nFilters];
        for (int i=0; i<nInputs; i++){
            cout << "****iteration: "<< i << endl;
            cout << "Predtor Value is: " << pred[i] << endl;
            for (int j=0; j<nFilters; j++){
                pred_filtered[i][j]=filterBanks[i]->doFilterBank(j, pred[i]);
                cout << "The "<< j << "th " << "filtered value is: " << pred_filtered[i][j] << endl;
            }
        }
        double* pred_pointer=pred_filtered[0];
        cout << pred_pointer[0] << " " << pred_pointer[1] << " " << pred_pointer[2] << " " << pred_pointer[3] << endl;

 #endif

#ifdef noFilter
        double* pred_pointer=pred;
#endif

#ifdef icoLearner
        int gain=100;

        ico->setInput(pred_pointer); //takes a pointer in
        ico->setError(error);
        ico->setLearningFactor(0.01);
        ico->updateWeights();
        ico->doSum();
        double icoOutput=ico->getOutput();
        double weightDistance= ico->getWeightsDistance();
        double weight1= ico->getWeight(0);
        double weight2= ico->getWeight(1);
        double error2 = (error + icoOutput) * gain;
        racer->leftSpeed  = speed; // + error2;
        racer->rightSpeed = speed - error2;


#ifdef positionMode
        Enki::Point position;
        position = racer->pos;
        double angle = racer->angle;
        //cout<< position.x << " " << position.y <<endl;
        //cout<< prevX << " " << prevY <<endl;
        double deltaX = position.x - prevX;
        double deltaY = position.y - prevY;
        //cout<< deltaX << " " << deltaY <<endl;
        prevX=position.x;
        prevY=position.y;
#endif

#endif

#ifdef bpLearner
        int gain=100;
        cout<< "MAIN PROGRAM: NEXT ITERATION"<<endl;
        net->setInputs(pred_pointer);
        double learningRate=0.01;
        net->setLearningRate(learningRate);
        net->propInputs();
        double leadError=error;
        net->setError(leadError);
        net->propError();
        net->updateWeights();
        //need to do weight change first
        net->saveWeights();
        double weightDistance=net->getWeightDistance();
        double Output= net->getOutput(0);
        double OutputSum= net->getSumOutput(0);
        double error2 = (error + Output) * gain;
        racer->leftSpeed  = speed + error2;
        racer->rightSpeed = speed - error2;

#endif

#endif
        line=line+1;

        std::ofstream myfileLeft;
        myfileLeft.open ("leftGround.txt", fstream::app);
        myfileLeft << line << " " << leftGround << "\n";
        myfileLeft.close();

        std::ofstream myfileRight;
        myfileRight.open ("rightGround.txt", fstream::app);
        myfileRight << line << " " << rightGround << "\n";
        myfileRight.close();

        std::ofstream myfile3;
        myfile3.open ("speeds.txt", fstream::app);
        myfile3 << line << " " << racer->leftSpeed << " " << racer->rightSpeed << "\n";
        myfile3.close();

#ifdef icoLearner
        std::ofstream myfilew;
        myfilew.open ("weights.txt", fstream::app);
        myfilew << line << " " << weightDistance << "\n";
        myfilew.close();
        std::ofstream myfilew1;
        myfilew1.open ("weight1.txt", fstream::app);
        myfilew1 << line << " " << weight1 << "\n";
        myfilew1.close();
        std::ofstream myfilew2;
        myfilew2.open ("weight2.txt", fstream::app);
        myfilew2 << line << " " << weight2 << "\n";
        myfilew2.close();
#endif

#ifndef reflex
#ifndef noFilter
        std::ofstream myfilep[nInputs];
        char c = '0';
        for (int p=0; p<nInputs; p++){
            string s = "predictor";
            c += 1;
            s += c;
            s += ".txt";
        myfilep[p].open (s, fstream::app);
        myfilep[p] << line << " " << pred[p] << " ";
#ifdef doFilter
        myfilep[p] << pred_filtered[p]<< "\n";
#endif
#ifdef filterBnk
        myfilep[p] << pred_filtered[p][0] << " "<< pred_filtered[p][1] << "\n";
#endif
        myfilep[p].close();
        }
#endif
#endif
	}
};

int main(int argc, char *argv[])
{
    srand(3);
    QApplication app(argc, argv);
    QImage gt;
    gt = QGLWidget::convertToGLFormat(QImage("cc.png"));
    if (gt.isNull()) {
        fprintf(stderr,"Texture file not found\n");
        exit(1);
    }
    const uint32_t *bits = (const uint32_t*)gt.constBits();
    World world(maxx, maxy,
                Color(1000, 1000, 1000), World::GroundTexture(gt.width(), gt.height(), bits));
    cout<<gt.width()<<" "<<gt.height()<<endl;
    EnkiPlayground viewer(&world);
    viewer.show();
    return app.exec();
}
