#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"


class FMSineSynth
{

    public:
    FMSineSynth();
    FMSineSynth(float volume);
    
    float play(             double  frequency, double modulationFrequency = 0.02);
    float play( std::vector<double> frequency, double modulationFrequency = 0.02);
    float play( int rootNote,                             double modulationFrequency=0.02);
    float play( int rootNote, std::vector<int> pitchDiff, double modulationFrequency = 0.02);

    // Getter / Setter
    void setVolume(short oscIndex, float volume);
    void setMasterVolume(float volume);
    void setModulationStrength(float ms);
    //enum class waveEnum { Square, SineWave, CosWave, Saw, Phasor, Triangle, Pulse, Impulse, Noise };

    static unsigned short clampToMidiNoteNum(int num) {
        return min(max(0, num),127);
    }

    private:
    // Oscilator Setup
    static const short NUM_OSC = 5;

    array<maxiOsc, NUM_OSC> carrierOscs;
          maxiOsc           modulationOsc;
    
    // Oscilator Parameter
          float           masterVolume;
    array<float, NUM_OSC> volume; // 0 ~ 1
          float           modulationStrength; // 0 ~ 1
};

