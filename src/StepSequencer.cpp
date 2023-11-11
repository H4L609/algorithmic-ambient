#include "StepSequencer.h"

StepSequencer::StepSequencer() {
    this->interval    = calculateIntervalInNumSamples();
    for (size_t i = 0; i < probabilities.size(); i++) {
        probabilities[i] = (1 - i % 8) / 8; // 1, 7/8, 6/8, 5/8, ...
    }
}

StepSequencer::StepSequencer(int bpm, int sampleRate, short bufferSize) {
    this->bpm         = bpm;
    this->sampleRate  = sampleRate;
    this->interval = calculateIntervalInNumSamples();
    this->elapsedTime = 0;
    this->bufferSize  = bufferSize;

    for (size_t i = 0; i < probabilities.size(); i++) {
        probabilities[i] = (8 - i % 8) / 8.0; // 1, 7/8, 6/8, 5/8, ...
        //cout << i << " : " << probabilities[i] << endl;
    }
    
}

void StepSequencer::update() {
    this->elapsedTime += this->bufferSize;

    if (fire) {
        fire = false;
        return;
    }

    if (this->elapsedTime - lastJudgeTime >= this->interval) {
        if (probabilities[observedNoteIndex] >= ofRandomf()*0.5 + 0.5) {
            fire = true;
        }
        lastJudgeTime= this->elapsedTime;
        observedNoteIndex = (observedNoteIndex+1)%32;
    }
}

void StepSequencer::judgeFire() {
    
}

unsigned int StepSequencer::calculateIntervalInNumSamples() {
    float  intervalInSecond = (4.0 / 32.0) * (60.0 / this->bpm);
    return unsigned int( floor( intervalInSecond * sampleRate ));
}

int  StepSequencer::getBpm() {return bpm ;}
void StepSequencer::setBpm(int newBpm) {
    this->bpm = newBpm;
    this->interval = calculateIntervalInNumSamples();
}

bool StepSequencer::getFire(){return fire; }
//void StepSequencer::setFire(bool val) { fire = val; }

void StepSequencer::setProbability(int index_plus_one, float percentage) {
    probabilities[(double)index_plus_one-1] = percentage;
}