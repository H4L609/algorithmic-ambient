
//
//  ofxLPF.cpp
//  Simple Low Pass Filter
//
//  Created by Koki Ibukuro on 6/17/14.
//
//

//http://baumdevblog.blogspot.jp/2010/11/butterworth-lowpass-filter-coefficients.html

#include "SimpleLPF.h"
#include <math.h>

SimpleLPF::SimpleLPF(const int samplerate, const double cutoff) {
    initialize(samplerate, cutoff);
}

void SimpleLPF::initialize(const int samplerate, const double cutoff) {
    double sqrt2 = 1.4142135623730950488;

    double QcRaw = (2 * PI * cutoff) / samplerate; // Find cutoff frequency in [0..PI]
    double QcWarp = tan(QcRaw); // Warp cutoff frequency

    double gain = 1 / (1 + sqrt2 / QcWarp + 2 / (QcWarp * QcWarp));
    by[2] = (1 - sqrt2 / QcWarp + 2 / (QcWarp * QcWarp)) * gain;
    by[1] = (2 - 2 * 2 / (QcWarp * QcWarp)) * gain;
    by[0] = 1;
    ax[0] = 1 * gain;
    ax[1] = 2 * gain;
    ax[2] = 1 * gain;
}

double SimpleLPF::process(double value) {
    xv[2] = xv[1];
    xv[1] = xv[0];
    xv[0] = value;
    yv[2] = yv[1]; yv[1] = yv[0];

    yv[0] = (ax[0] * xv[0] + ax[1] * xv[1] + ax[2] * xv[2]
        - by[1] * yv[0]
        - by[2] * yv[1]);
    return yv[0];
}