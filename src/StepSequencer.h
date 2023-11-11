#pragma once

#include "ofMain.h"

/*
* bpm���w�肵�A�e���[�v���̃m�[�c���Ƃ�"���Η�"�ɏ]���ăm�[�g�����΂�����X�L�b�v�����
* �ő�32�������܂ŉ������߂�
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

    // ���Ԋ֘A
    unsigned short bpm         = 120;
             int   sampleRate  = 44100;
    unsigned long  elapsedTime = 0;
    unsigned int   lastJudgeTime= 0;
    unsigned int   interval;

    // ���Ί֘A
    bool  fire         = true;
    short observedNoteIndex = 0;
    std::array<float, 32> probabilities;
};

