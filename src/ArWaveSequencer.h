#pragma once

#include "ofMain.h"

class ArWaveSequencer
{
public:
	ArWaveSequencer();
	ArWaveSequencer(int sampleRate, int bufferSize);

	unsigned int calculateIntervalInNumSamples();

	float getValue();

	void setFrequency(float freq);
	void setOffset(float second);

	void setSampleRate(int sr);
	void setBufferSize(int bs);


	void setAttackPow(float ap);
	void setReleasePow(float rp);
	void setArBoundary(float pos);
	void setMinMax(float mi, float ma);

	void update();


private:
	// General Settings
	int   sampleRate = 44100;
	int   bufferSize = 256;

	// コンピュータが計算する部分
	unsigned long  elapsedTime = 0;
	int            interval; // num sample
	float          phase = 0.0f;

	// 任意に設定する部分
	float          frequency = 1.0;
	float          offset = 0.0;

	float arBoundary = 0.5;
	float attackPow  = 2;
	float releasePow = 2;
	float minVal	 = 0;
	float maxVal     = 1;



};
