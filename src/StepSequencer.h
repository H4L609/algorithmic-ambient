#pragma once

#include "ofMain.h"

/*
* bpmを指定し、各ループ内のノーツごとの"発火率"に従ってノートが発火したりスキップされる
* 最大32分音符まで音を刻める
*/
class StepSequencer
{
    public:
    StepSequencer();
    StepSequencer(int bpm, int sampleRate);
    StepSequencer(int bpm, int sampleRate, short bufferSize);

    void update();
    void judgeFire();

    unsigned int calculateIntervalInNumSamples();

    int  getBpm();
    void setBpm(int newBpm);

    void setProbability(int index_plus_one, float percentage);

    bool getFire();
    //void setFire(bool val);

    int getObservedNoteIndex() {
        return observedNoteIndex;
    }

    private:

    short bufferSize=256;

    // 時間関連
    unsigned short bpm         = 120;
             int   sampleRate  = 44100;
    unsigned long  elapsedTime = 0;
    unsigned int   lastJudgeTime= 0;
    unsigned int   interval;

    // 発火関連
    bool  fire         = true;
    short observedNoteIndex = 0;
    std::array<float, 32> probabilities;
};

