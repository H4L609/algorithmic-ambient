#pragma once

#include "ofMain.h"
#include "StepSequencer.h"
#include "ofxMaxim.h"
#include "DroneSinewave.h"
#include "PositionChaser.h"
#include "RadialKnob.h"

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

		// Interaction
		float percentX;
		float percentY;

		PositionChaser mouseChaser;
		PositionChaser rotateChaser;

		RadialKnob knob1;
		RadialKnob knob2;
		RadialKnob knob3;
		RadialKnob knob4;

		// Audio
		//void audioIn(ofSoundBuffer& input) override; // not used in this example
		void audioOut(ofSoundBuffer& output) override;

		StepSequencer stepSequencer;
		maxiOsc oscillator1;
		maxiOsc oscillator2;

		DroneSineWave drone1;
		DroneSineWave drone2;

		double pitch;
};
