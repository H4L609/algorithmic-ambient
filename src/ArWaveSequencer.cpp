#include "ArWaveSequencer.h"

ArWaveSequencer::ArWaveSequencer() {
    this->intervalNumSample = sampleRate / frequency;
}
ArWaveSequencer::ArWaveSequencer(int sampleRate, int bufferSize) {
    this->sampleRate = sampleRate;
    this->bufferSize = bufferSize;

    this->intervalNumSample = sampleRate / frequency;
}

void ArWaveSequencer::setOffset(float offsetPhase) {
    this->offset = glm::fract(phase);
}

void ArWaveSequencer::setAttackPow(float ap) {
    this->attackPow = ap;
}
void ArWaveSequencer::setReleasePow(float rp) {
    this->releasePow = rp;
}

void ArWaveSequencer::setArBoundary(float boundary) {
    this->arBoundary = clamp(boundary, 0.0f, 1.0f);
}
void ArWaveSequencer::setFrequency(float freq) {
    this->frequency = freq;
}

float ArWaveSequencer::getValue() {
    float attackWave = max(glm::fract(this->phase) - this->arBoundary, 0.0f) / (1 - arBoundary);
    float releaseWave = max(glm::fract(1.0f - this->phase) - (1.0f - this->arBoundary), 0.0f) / arBoundary;

    return pow(attackWave, attackPow) + pow(releaseWave, releasePow);
}



void ArWaveSequencer::update() {
    this->elapsedTime += this->bufferSize;
    this->phase = (this->elapsedTime % this->intervalNumSample) / (float)intervalNumSample;
    this->phase = glm::fract(this->phase + offset);
}

unsigned int ArWaveSequencer::calculateIntervalInNumSamples() {
    return unsigned int(floor(sampleRate / this->frequency));
}