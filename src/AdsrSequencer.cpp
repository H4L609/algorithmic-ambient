#include "AdsrSequencer.h"

AdsrSequencer::AdsrSequencer(){
    this->intervalNumSample = sampleRate / frequency;
}
AdsrSequencer::AdsrSequencer(int sampleRate, int bufferSize) {
    this->sampleRate = sampleRate;
    this->bufferSize = bufferSize;

    this->intervalNumSample = sampleRate / frequency;
}

void AdsrSequencer::setOffset(float offsetPhase) {
    this->offset = glm::fract(phase);
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

float AdsrSequencer::getValue() {
    float attackWave = max(glm::fract(this->phase) - this->arBoundary, 0.0f) / (1 - arBoundary);
    float releaseWave = max(glm::fract(1.0f - this->phase) - (1.0f - this->arBoundary), 0.0f) / arBoundary;

    return pow(attackWave, attackPow) + pow(releaseWave, releasePow);
}



void AdsrSequencer::update() {
    this->elapsedTime += this->bufferSize;
    this->phase = (this->elapsedTime % this->intervalNumSample) / (float)intervalNumSample;
    this->phase = glm::fract(this->phase+offset);
}

unsigned int AdsrSequencer::calculateIntervalInNumSamples() {
    return unsigned int(floor(sampleRate / this->frequency));
}