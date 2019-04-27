# -*- coding: utf-8 -*-
"""
Created on Sat Jul  7 18:13:03 2018

@author: sama
"""

import numpy as np
import matplotlib.pylab as plt
import bpPlotClass as bpc
plt.rcParams['font.family'] = 'serif'
plt.rcParams.update({'font.size': 14})

path='/home/sama/Documents/enki-1/examples/line_follower/'
sizeY=3
ratioYX=3
my_dpi=100

plt.close("all")

statRaw=np.loadtxt('stat.txt')
stat=statRaw.astype(np.int16)
numPredictors=stat[0]
numLayerNeurons=stat[1::]

errordata=np.loadtxt('error.txt'); error=errordata[:,1]
minE=min(error); maxE=max(abs(error))
errorNorm=error/maxE

efig=plt.figure('error', figsize=(sizeY*ratioYX,sizeY), dpi=my_dpi)
axe=efig.add_subplot(111)
plt.plot(errorNorm, color='black')
plt.ylabel('Error Signal')
plt.ylim(-1.1, 1.1)
plt.yticks([-1,0,1])
plt.xticks([0,len(errorNorm)])
axe.set_aspect(aspect=len(errorNorm)/(2.2*ratioYX))
efig.savefig(path+'BP_error', quality= 95, fromat='svg', bbox_inches='tight')

for i in range(numPredictors):
    predictor=bpc.predictor(i+1)
    predictor.plotPredictor(errorNorm)
    
for j in range(len(numLayerNeurons)):
    for k in range(numLayerNeurons[j]):
        neuron=bpc.neuron(int(str(j+1)+str(k+1)))
        neuron.plotWeights()

for n in range(len(numLayerNeurons)-1):
    layer=bpc.layer(n+1)
    layer.plotLayerWeights()
    
finalLayer=bpc.finalLayer(len(numLayerNeurons))
finalLayer.plotFinalLayerWeights()

