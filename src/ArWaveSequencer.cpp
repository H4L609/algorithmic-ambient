#include "ArWaveSequencer.h"

ArWaveSequencer::ArWaveSequencer() {
    this->interval = sampleRate / frequency;
}
ArWaveSequencer::ArWaveSequencer(int sampleRate, int bufferSize) {
    this->sampleRate = sampleRate;
    this->bufferSize = bufferSize;

    this->interval = sampleRate / frequency;
}

// General Setting
void ArWaveSequencer::setSampleRate(int sr) {
    this->sampleRate = sr;
}
void ArWaveSequencer::setBufferSize(int bs) {
    this->bufferSize = bs;
}

// Envelope Parameters
void ArWaveSequencer::setAttackPow(float ap) {
    this->attackPow = ap;
}
void ArWaveSequencer::setReleasePow(float rp) {
    this->releasePow = rp;
}
void ArWaveSequencer::setArBoundary(float boundary) {
    this->arBoundary = clamp(boundary, 0.0f, 1.0f);
}
void ArWaveSequencer::setMinMax(float mi, float ma){
    if (mi > ma) swap(mi, ma);
    this->minVal = clamp(mi,0.0f, 1.0f);
    this->maxVal = clamp(ma,0.0f, 1.0f);
}

// Sonic Parameter
void ArWaveSequencer::setFrequency(float freq) {
    this->frequency = freq;
    this->interval = sampleRate / this->frequency;
}
void ArWaveSequencer::setOffset(float offsetPhase) {
    this->offset = glm::fract(phase); 
}

float ArWaveSequencer::getValue() {
    float attackWave = max(glm::fract(this->phase) - this->arBoundary, 0.0f) / (1 - arBoundary);
    float releaseWave = max(glm::fract(1.0f - this->phase) - (1.0f - this->arBoundary), 0.0f) / arBoundary;

    float  val = pow(attackWave, attackPow) + pow(releaseWave, releasePow);
           //val = val*(maxVal - minVal)+minVal; // 設定した最大値と最低値の間にセット
    return clamp(val, minVal, maxVal);
}



void ArWaveSequencer::update() {
    this->elapsedTime += this->bufferSize;
    this->phase = (this->elapsedTime % this->interval) / (float)interval;
    this->phase = glm::fract(this->phase + offset);
}

unsigned int ArWaveSequencer::calculateIntervalInNumSamples() {
    return unsigned int(floor(sampleRate / this->frequency));
}