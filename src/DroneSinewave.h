#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"


class DroneSineWave
{

    public:
    DroneSineWave();
    DroneSineWave(float volume);
    float play(std::vector<double> frequency);

    // Getter / Setter
    void setVolume(short oscIndex, float volume);
    void setMasterVolume(float volume);
    //enum class waveEnum { Square, SineWave, CosWave, Saw, Phasor, Triangle, Pulse, Impulse, Noise };


    private:
    // Oscilator Setup
    static const short NUM_OSC = 4;
    float masterVolume;
    array<float,   NUM_OSC> volume; // 0 ~ 1

    array<maxiOsc, NUM_OSC> carrierOscs;
          maxiOsc           modulationOsc;


};

