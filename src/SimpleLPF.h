//
//  ofxLPF.h
//  Simple Low Pass Filter
//
//  Created by Koki Ibukuro on 6/17/14.
//
//

#pragma once
#include "ofMain.h"

class SimpleLPF {
public:
    SimpleLPF(const int samplerate = 44100, const double cutoff = 1000);
    void initialize(const int samplerate, const double cutoff);
    double process(double value);

private:
    double ax[3];
    double by[3];
    double xv[3];
    double yv[3];
};