#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(250);

    //Initialize the drawing variables
    for (int i = 0; i < ofGetWidth(); ++i) {
        waveform[i] = 0;
    }
    waveIndex = 0;

    soundStream.printDeviceList();

    sampleRate = 44100; /* Sampling Rate */
    bufferSize = 256; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);

    // Synthesize Setup

    melody_01;
    melody_02;

    fm_pad_01;
    fm_pad_02;

    hicutNoise_01;
    hicutNoise_02;
    bandpassNoise;


    // Sequencer Setup
    int bpm=120;
    stepSequencer=StepSequencer(bpm, sampleRate, bufferSize);
    arseq1.setSampleRate(sampleRate);
    arseq1.setBufferSize(bufferSize);
    arseq2.setSampleRate(sampleRate);
    arseq2.setBufferSize(bufferSize);
    arseq3.setSampleRate(sampleRate);
    arseq3.setBufferSize(bufferSize);
    arseq4.setSampleRate(sampleRate);
    arseq4.setBufferSize(bufferSize);
    arseq5.setSampleRate(sampleRate);
    arseq5.setBufferSize(bufferSize);
    arseq6.setSampleRate(sampleRate);
    arseq6.setBufferSize(bufferSize);
    arseq7.setSampleRate(sampleRate);
    arseq7.setBufferSize(bufferSize);

    //for (int i = 0; i < 32; i++) {
    //    stepSequencer.setProbability(i+1, 0);
    //}
    //stepSequencer.setProbability(0  + 1, 1);
    //stepSequencer.setProbability(8  + 1, 1);
    //stepSequencer.setProbability(16 + 1, 1);
    //stepSequencer.setProbability(24 + 1, 1);

    // Setup ofSoundStream
    ofSoundStreamSettings settings;
    settings.setOutListener(this);
    settings.sampleRate = sampleRate;
    settings.numOutputChannels = 2;
    settings.numInputChannels = 0;
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);

    // Interaction Parameter
    mouseChaser.weight = 0.05f;

    // Layout
    knobMargin = 90;
    knobChannel= 0;
    knobActivationPattern= 0;
    knobActivationPatternVariation=4;
    knobLayout = array<glm::vec2, 4>{
        glm::vec2(ofGetWidth() / 2 - knobMargin, ofGetHeight() / 2 - knobMargin), // 1
        glm::vec2(ofGetWidth() / 2 + knobMargin, ofGetHeight() / 2 - knobMargin), // 2
        glm::vec2(ofGetWidth() / 2 + knobMargin, ofGetHeight() / 2 + knobMargin), // 3
        glm::vec2(ofGetWidth() / 2 - knobMargin, ofGetHeight() / 2 + knobMargin), // 4
        //glm::vec2(ofGetWidth() / 2 + knobMargin, ofGetHeight() / 2             ), // 5
        //glm::vec2(ofGetWidth() / 2 - knobMargin, ofGetHeight() / 2 - knobMargin), // 6
        //glm::vec2(ofGetWidth() / 2             , ofGetHeight() / 2 - knobMargin), // 7
        //glm::vec2(ofGetWidth() / 2 + knobMargin, ofGetHeight() / 2 - knobMargin), // 8
    };
    for (int i = 0; i < knobs.size(); i++) { knobs[i].setCenterPos(knobLayout[i]); }


    font.load("verdana.ttf", 50, true, true);
    font.setLineHeight(70.0f);
    font.setLetterSpacing(5.037);
}

//--------------------------------------------------------------
void ofApp::update(){
    // Mouse Position
    mouseChaser.chase(glm::vec2(mouseX, mouseY)) ;

    // Interactive Params
    percentX = mouseChaser.x / ofGetWidth();
    percentY = mouseChaser.y / ofGetHeight();

    pitch =percentY*percentY;
    pitch*=20000;
    pitch =clamp(pitch, 10.0, 20000.0);

    //drone1.setMasterVolume(percentY * percentY);
    //drone2.setMasterVolume(percentY * percentY);

    fm_pad_01.setMasterVolume(pow(percentX, 1.4)* 0.8);
    fm_pad_02.setMasterVolume(pow(percentX, 1.4)* 0.8);

    for (int i=0; i<knobs.size();i++){knobs[i].update();}

    volume_whiteNoise = knobs[0].getAngularValue();
    volume_sparkNoise = knobs[1].getAngularValue();
    volume_co2Noise   = knobs[2].getAngularValue()*0;
    //volume_whiteNoise = knobs[0].getAngularValue();
}

//--------------------------------------------------------------
void ofApp::draw(){

    // GUI : Mouse / Knob
    ofSetColor(ofColor::darkBlue);
    //ofDrawCircle(mouseChaser.getPositionVec2(), 10);

    ofSetColor(ofColor::lightBlue);
    //ofDrawCircle(mouseX, mouseY, 10);

    for (int i = 0; i < knobs.size(); i++) {
        knobs[i].aim(mouseChaser.getPositionVec2());
        //knobs[i].draw();
    }

    //ofSetColor(0, 0, 0, 1);
    ofSetColor(ofColor::black);

    // Debug Values9
    int fontSize = 30;
    int debugMessageX = 20;
    int debugMessageY = 20;
    font.drawString("Generative Noise Music", ofGetWidth()/2, ofGetHeight()/2);
    ofDrawBitmapString("Mouse ( X , Y ) : " + to_string(mouseChaser.x) + " , " + to_string(mouseChaser.y), debugMessageX, debugMessageY);
    debugMessageY += fontSize;
    ofDrawBitmapString("Percentge ( X , Y ) : " + to_string(percentX) + " , " + to_string(percentY), debugMessageX, debugMessageY);
    debugMessageY += fontSize;

    ofDrawBitmapString("Pitch : " + to_string(pitch), debugMessageX, debugMessageY);
    debugMessageY += fontSize;

    ofDrawBitmapString("Knob1 Dir : "   + to_string(knobs[0].getDirection().x) + " , " + to_string(knobs[0].getDirection().y), debugMessageX, debugMessageY);
    debugMessageY += fontSize;
    ofDrawBitmapString("Knob1 Angle : " + to_string(knobs[0].getAngle()), debugMessageX, debugMessageY);
    debugMessageY += fontSize;
    ofDrawBitmapString("Knob1 Value : " + to_string(knobs[0].getAngularValue()), debugMessageX, debugMessageY);
    debugMessageY += fontSize;
    ofDrawBitmapString("AR Seq 1 Value : " + to_string(arseq1.getValue()), debugMessageX, debugMessageY);
    debugMessageY += fontSize;
    ofDrawBitmapString("Active Knob : " + to_string(knobChannel), debugMessageX, debugMessageY);
    debugMessageY += fontSize;
    ofDrawBitmapString("Knob Activation Pattern : " + to_string(knobActivationPattern), 20, debugMessageY);
    debugMessageY += fontSize;

    /////////////// waveform
    ofTranslate(0, ofGetHeight() / 2);
    ofSetColor(0, 50, 0);
    ofFill();
    ofDrawLine(0, 0, 1, waveform[1] * ofGetHeight() / 2.); //first line
    for (int i = 1; i < (ofGetWidth() - 1); ++i) {
        ofDrawLine(i, waveform[i] * ofGetHeight() / 2., i + 1, waveform[i + 1] * ofGetHeight() / 2.);
    }

}

void ofApp::audioOut(ofSoundBuffer& output) {

    stepSequencer.update();
    //if (stepSequencer.getFire()) {
        //cout << "Fire : " << stepSequencer.getObservedNoteIndex() << " - " << ofGetElapsedTimef() << endl;
    std::size_t outChannels = output.getNumChannels();
    for (int i = 0; i < output.getNumFrames(); ++i) {
        output[i * outChannels]  = 0;

        int rootNote = 69;
        vector<int> harmonicNote;
        harmonicNote.push_back(4);
        harmonicNote.push_back(7);
        harmonicNote.push_back(11);
        harmonicNote.push_back(13);
        harmonicNote.push_back(83);

        //// Hicut Noise Wave 01
        arseq1.setFrequency(0.07);
        arseq1.setArBoundary(0.4);
        arseq1.setOffset(0.2);
        arseq1.setAttackPow(2.0);
        arseq1.setReleasePow(0.7);
        arseq1.setMinMax(0.1, 1);

        hicutNoise_01.setVolume(0.1);
        hicutFilter_01.initialize(sampleRate, 700* arseq1.getValue());
        float out_hicutNoise_01 = hicutFilter_01.process((double)hicutNoise_01.play());
        out_hicutNoise_01 = volume_whiteNoise;

        //// Hicut Noise Wave 02
        arseq2.setFrequency(0.11);
        arseq2.setArBoundary(0.3);
        arseq2.setAttackPow(2.0);
        arseq2.setReleasePow(1.2);
        arseq2.setMinMax(0.1, 1);

        hicutNoise_02.setVolume(0.7);
        hicutFilter_02.initialize(sampleRate, 2000 * arseq2.getValue());
        float out_hicutNoise_02 = hicutFilter_02.process((double)hicutNoise_02.play());
        out_hicutNoise_02 = volume_whiteNoise;

        //// Hicut Noise Wave 03
        arseq3.setFrequency(0.09);
        arseq3.setArBoundary(0.2);
        arseq3.setAttackPow(2.0);
        arseq3.setReleasePow(1.2);
        arseq3.setMinMax(0.01, 1);

        hicutNoise_03.setVolume(0.2);
        hicutFilter_03.initialize(sampleRate, 3000 * arseq3.getValue());
        float out_hicutNoise_03 = hicutFilter_03.process((double)hicutNoise_03.play());
        out_hicutNoise_03 = volume_whiteNoise;

        // Hicut Noise Wave 04
        arseq4.setFrequency(0.03);
        arseq4.setArBoundary(0.5);
        arseq4.setAttackPow(2.5);
        arseq4.setReleasePow(0.7);
        arseq4.setMinMax(0.2, 1.0);

        hicutNoise_04.setVolume(0.4);
        hicutFilter_04.initialize(sampleRate, 1500.0 * arseq4.getValue());
        float out_hicutNoise_04 = hicutFilter_04.process((double)hicutNoise_04.play());
        out_hicutNoise_04 = volume_whiteNoise;
        

        output[i * outChannels] += 
              out_hicutNoise_01
            + out_hicutNoise_03
            + out_hicutNoise_02 * 0.3
        ;
        output[i * outChannels+1] += 
              out_hicutNoise_02
            + out_hicutNoise_04
            + out_hicutNoise_03*0.3
        ;


        // Spark Noise
        arseq5.setFrequency(6* arseq5.getValue());
        arseq5.setArBoundary(0.13);
        arseq5.setAttackPow(2.0);
        arseq5.setReleasePow(3.0);
        arseq5.setMinMax(0.1, 1.0);

        sparkNoise_01.setVolume(0.4);
        sparkNoiseFilter_01.initialize(sampleRate, 2000 * arseq5.getValue());
        float out_sparkNoise_01 = sparkNoiseFilter_01.process((double)sparkNoise_01.play()) * arseq5.getValue();
        //out_sparkNoise_01 *= volume_sparkNoise;


        arseq6.setFrequency(1.1 * arseq6.getValue());
        arseq6.setArBoundary(0.4);
        arseq6.setAttackPow(2.0);
        arseq6.setReleasePow(3.0);
        arseq6.setMinMax(0.1, 1.0);

        sparkNoise_02.setVolume(0.4);
        sparkNoiseFilter_02.initialize(sampleRate, 4000 * arseq6.getValue());
        float out_sparkNoise_02 = sparkNoiseFilter_02.process((double)sparkNoise_02.play()) * arseq6.getValue();
        //out_sparkNoise_02 *= volume_sparkNoise;
        // walk noise
        arseq7.setFrequency(1.3);
        arseq7.setArBoundary(0.15);
        arseq7.setAttackPow(8.0);
        arseq7.setReleasePow(8.0);
        arseq7.setMinMax(0.1, 1.0);

        walkNoise_01.setVolume(0.1);
        walkNoiseFilter_01.initialize(sampleRate, 10000 * arseq7.getValue());
        float out_walkNoise_01 = walkNoiseFilter_01.process((double)walkNoise_01.play() * arseq7.getValue());
        out_walkNoise_01 *= volume_co2Noise;

        output[i * outChannels  ] +=
            +out_sparkNoise_01
            +out_walkNoise_01
        ;
        output[i * outChannels+1] += 
            +out_sparkNoise_02
            + out_walkNoise_01
        ;





        //Hold the values so the draw method can draw them
        waveform[waveIndex] = output[i * outChannels];
        if   (waveIndex < (ofGetWidth() - 1)) { ++waveIndex; }
        else { waveIndex = 0; }
        }
    //}
    arseq1.update();
    arseq2.update();
    arseq3.update();
    arseq4.update();
    arseq5.update();
    arseq6.update();
    arseq7.update();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

    string s = ofUTF8ToString(key);
    if      (s == "0") { knobChannel = 0;}
    else if (s == "1") { knobChannel = 1;}
    else if (s == "2") { knobChannel = 2;}
    else if (s == "3") { knobChannel = 3;}
    else if (s == "4") { knobChannel = 4;}

    switch (knobChannel) {
        case 0:
            knobChannel = 0;

            for (int i = 0; i < knobs.size(); i++) {
                    knobs[i].ON();
            }
            break;
        case 1:
            knobChannel = 1;

            for (int i = 0; i < knobs.size(); i++) {
                knobs[i].OFF();
            }
            knobs[0].ON();
            

            break;
        case 2:
            knobChannel = 2;

            for (int i = 0; i < knobs.size(); i++) {
                knobs[i].OFF();
            }
            knobs[1].ON();
            break;
        case 3:
            knobChannel = 3;

            for (int i = 0; i < knobs.size(); i++) {
                knobs[i].OFF();
            }
            knobs[2].ON();
            break;
        case 4:
            knobChannel = 4;

            for (int i = 0; i < knobs.size(); i++) {
                knobs[i].OFF();
            }
            knobs[3].ON();
            break;
    }/*
    if (key == OF_KEY_UP || ofUTF8ToString(key) == "e") {
        knobActivationPattern++;
        knobActivationPattern %= knobActivationPatternVariation;
        cout << "KEYUP"   << knobActivationPattern << endl;


    }
    if (key == OF_KEY_DOWN || ofUTF8ToString(key) == "q") {
        knobActivationPattern--;
        knobActivationPattern+= knobActivationPatternVariation;
        knobActivationPattern %= knobActivationPatternVariation;
        cout << "KEYDOWN" << knobActivationPattern << endl;
    }*/
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    for (int i = 0; i < knobs.size(); i++) {
        knobs[i].setCenterPos(knobLayout[i]);
    }
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
