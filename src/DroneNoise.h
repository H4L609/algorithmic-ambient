#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"


class DroneNoise
{

public:
    DroneNoise();
    DroneNoise(float volume);
    float play();

    void setVolume(float volume);

    void setSampleRate(int sr);
    void setBufferSize(int bs);

private:
    int   sampleRate = 44100;
    int   bufferSize = 256;

    float volume=0.05;
    maxiOsc noiseOsc;


};


