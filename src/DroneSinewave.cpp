#include "DroneSinewave.h"

DroneSineWave::DroneSineWave() {
    DroneSineWave(0.5); 
}

DroneSineWave::DroneSineWave(float volume) {
    masterVolume=1.0f;
    volume = clamp(volume, 0.0f, 1.0f);
    this->volume[0] = volume;
    this->volume[1] = volume;
    this->volume[2] = volume;
    this->volume[3] = volume;
}

void DroneSineWave::setVolume(short oscIndex, float volume) {
    volume =clamp(volume, 0.0f, 1.0f);
    this->volume[oscIndex]=volume;
}

void DroneSineWave::setMasterVolume(float volume) {
    volume = clamp(volume, 0.0f, 1.0f);
    this->masterVolume = volume;
}

float DroneSineWave::play(std::vector<double> frequency){
    float val=0.0;

    for (size_t i = 0; i < NUM_OSC; i++) {
        // 渡す周波数の個数がオシレーターの数より少ないとき、
        // 余分なオシレーターはミュートしつつ位相を進める
        
        if (frequency.size() <= i) {
            carrierOscs[i].sinewave(440);
            continue;
        }
        val+= carrierOscs[i].sinewave(frequency[i]*(1.0+modulationOsc.sinewave(0.01)*0.02));
    }
    return val*masterVolume;
}
