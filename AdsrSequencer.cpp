#include "AdsrSequencer.h"

AdsrSequencer::AdsrSequencer(){}
AdsrSequencer::AdsrSequencer(int sampleRate, int bufferSize) {
    this->sampleRate = sampleRate;
    this->bufferSize = bufferSize;
}

void AdsrSequencer::setAttackPow(float ap) {
    this->attackPow  = ap;
}
void AdsrSequencer::setReleasePow( float rp) {
    this->releasePow = rp;
}

void AdsrSequencer::setArBoundary(float boundary) {
    this->arBoundary = clamp(boundary, 0.0f, 1.0f);
}
void AdsrSequencer::setFrequency(float freq) {
    this->frequency = freq;
}


void AdsrSequencer::update() {
    this->elapsedTime += this->bufferSize;
    this->phase = (this->elapsedTime % this->intervalNumSample) / (float)intervalNumSample;
    this->phase = fmod(this->phase, 1.0f);
}

unsigned int AdsrSequencer::calculateIntervalInNumSamples() {
    return unsigned int(floor(sampleRate / this->frequency));
}