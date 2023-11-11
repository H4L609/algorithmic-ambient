#include "DroneNoise.h"

DroneNoise::DroneNoise() {
    this->volume = volume;
}

DroneNoise::DroneNoise(float volume) {
    this->volume = volume;
}

void DroneNoise::setSampleRate(int sr) {
    this->sampleRate = sr;
}
void DroneNoise::setBufferSize(int bs) {
    this->bufferSize = bs;
}

void DroneNoise::setVolume(float volume) {
    volume = clamp(volume, 0.0f, 1.0f);
    this->volume = volume;
}

float DroneNoise::play() {
    return noiseOsc.noise() * this->volume;
}
