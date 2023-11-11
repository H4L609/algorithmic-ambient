#include "FMSineSynth.h"

FMSineSynth::FMSineSynth() {
    FMSineSynth(0.5); 
}

FMSineSynth::FMSineSynth(float volume) {
    masterVolume=1.0f;
    volume = clamp(volume, 0.0f, 1.0f);
    this->volume[0] = volume;
    this->volume[1] = volume;
    this->volume[2] = volume;
    this->volume[3] = volume;
    this->volume[4] = volume;

    modulationStrength=1.0;
}

void FMSineSynth::setMasterVolume(float volume) {
    volume = clamp(volume, 0.0f, 1.0f);
    this->masterVolume = volume;
}
void FMSineSynth::setVolume(short oscIndex, float volume) {
    volume =clamp(volume, 0.0f, 1.0f);
    this->volume[oscIndex]=volume;
}
void FMSineSynth::setModulationStrength(float ms){
    this->modulationStrength = ms;
}


float FMSineSynth::play(            double  frequency, double modulationFrequency) {
    float modulation = modulationOsc.sinewave(modulationFrequency) * modulationStrength;
    for (size_t i = 1; i < NUM_OSC; i++) {
        // 渡す周波数の個数がオシレーターの数より少ないとき、
        // 余分なオシレーターはバイパスして鳴らす => 位相を進めるため
        carrierOscs[i].sinewave(440);
    }
    return carrierOscs[0].sinewave(frequency * (1.0 + modulation));
}

float FMSineSynth::play(std::vector<double> frequency, double modulationFrequency){
    float val=0.0;

    float modulation=modulationOsc.sinewave(modulationFrequency) * modulationStrength;

    for (size_t i = 0; i < NUM_OSC; i++) {
        // 渡す周波数の個数がオシレーターの数より少ないとき、
        // 余分なオシレーターはミュートしつつ位相を進める
        
        if (frequency.size() <= i) {
            carrierOscs[i].sinewave(440);
            continue;
        }
        val+= carrierOscs[i].sinewave(frequency[i]*(1.0+modulation));
    }
    return val*masterVolume;
}

float FMSineSynth::play(int rootNote,                             double modulationFrequency) {

    float modulation = modulationOsc.sinewave(modulationFrequency) * modulationStrength;

    for (size_t i = 1; i < NUM_OSC; i++) {
        // 渡す周波数の個数がオシレーターの数より少ないとき、
        // 余分なオシレーターはバイパスして鳴らす => 位相を進めるため
        carrierOscs[i].sinewave(440);
    }
    return carrierOscs[0].sinewave(convert::mtof(rootNote)*(1.0 + modulation));
}

float FMSineSynth::play(int rootNote, std::vector<int> pitchDiff, double modulationFrequency) {
    float val=0;
    float modulation = modulationOsc.sinewave(modulationFrequency) * modulationStrength;

    vector<double> frequency;
    rootNote = clampToMidiNoteNum(rootNote);
    frequency.push_back(convert::mtof(rootNote));
    
    for (int i = 0; i < NUM_OSC-1; i++) {
        int note = clampToMidiNoteNum(rootNote + pitchDiff[i]);
        frequency.push_back(convert::mtof(note) * (1.0 + modulation));
    }
    return this->play(frequency);
}

