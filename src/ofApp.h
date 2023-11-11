#pragma once

#include "ofMain.h"
#include "StepSequencer.h"
#include "ofxMaxim.h"
#include "FMSineSynth.h"
#include "PositionChaser.h"
#include "RadialKnob.h"
#include "ArWaveSequencer.h"
#include "knobActiveChart.cpp"
#include "DroneNoise.h."
#include "simpleLPF.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		// For drawing
		float waveform[4096]; //make this bigger, just in case
		int waveIndex;
		
		ofSoundStream soundStream;

		// Interaction Parameter & Objects
		float percentX;
		float percentY;

		PositionChaser mouseChaser;
		PositionChaser rotateChaser;

		array<RadialKnob, 8> knobs;
		array<glm::vec2, 8>  knobLayout;
		int                  knobMargin;
		int                  knobChannel;
		int                  knobActivationPattern;
		int					 knobActivationPatternVariation;


		// Audio
		//void audioIn(ofSoundBuffer& input) override; // not used in this example
		void audioOut(ofSoundBuffer& output) override;
		int sampleRate = 44100; /* Sampling Rate */
		int bufferSize = 256;

		StepSequencer stepSequencer;

		maxiOsc     melody_01;
		maxiOsc     melody_02;

		FMSineSynth fm_pad_01;
		FMSineSynth fm_pad_02;

		// Wave Noise
		DroneNoise		hicutNoise_01;
		SimpleLPF		hicutFilter_01;
		ArWaveSequencer arseq1;

		DroneNoise		hicutNoise_02;
		SimpleLPF		hicutFilter_02;
		ArWaveSequencer arseq2;

		DroneNoise		hicutNoise_03;
		SimpleLPF		hicutFilter_03;
		ArWaveSequencer arseq3;

		DroneNoise      hicutNoise_04;
		SimpleLPF       hicutFilter_04;
		ArWaveSequencer arseq4;

		// Spark Noise
		DroneNoise      sparkNoise_01;
		SimpleLPF       sparkNoiseFilter_01;
		ArWaveSequencer arseq5;

		DroneNoise      sparkNoise_02;
		SimpleLPF       sparkNoiseFilter_02;
		ArWaveSequencer arseq6;

		// Walking Noise
		DroneNoise      walkNoise_01;
		SimpleLPF       walkNoiseFilter_01;
		ArWaveSequencer arseq7;

		DroneNoise bandpassNoise;

		double pitch;
};
