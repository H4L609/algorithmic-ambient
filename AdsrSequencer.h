#pragma once

#include "ofMain.h"

class AdsrSequencer
{
	public:
	AdsrSequencer();
	AdsrSequencer(int sampleRate, int bufferSize);

	unsigned int calculateIntervalInNumSamples();

	void setFrequency(float freq);
	void setAttackPow (float ap);
	void setReleasePow(float rp);
	void setArBoundary(float pos);

	void update();


	private:
	int   sampleRate = 44100;
	int   bufferSize = 256;

	float          frequency   = 1.0;
	unsigned long  elapsedTime = 0;
	float          offset      = 0.0;
	int            intervalNumSample; // num sample
	float phase = 0.0f;

	float arBoundary = 0.5;
	float attackPow  = 2;
	float releasePow = 2;

        

};
