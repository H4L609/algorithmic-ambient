#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"


class DroneNoise
{

public:
    DroneNoise();
    DroneNoise(float volume);
    float play(std::vector<double> frequency);

    // Getter / Setter
    void setVolume(short oscIndex, float volume);
    void setMasterVolume(float volume);
    //enum class waveEnum { Square, SineWave, CosWave, Saw, Phasor, Triangle, Pulse, Impulse, Noise };


private:
    // Oscilator Setup
    static const short NUM_OSC = 1;
    float volume;
    maxiOsc noiseOsc;


};


