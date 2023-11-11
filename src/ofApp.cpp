#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(250);

    //Initialize the drawing variables
    for (int i = 0; i < ofGetWidth(); ++i) {
        waveform[i] = 0;
    }
    waveIndex = 0;


    int sampleRate = 44100; /* Sampling Rate */
    int bufferSize = 256; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);

    // Sequencer Setup
    int bpm=120;
    stepSequencer=StepSequencer(bpm, sampleRate, bufferSize);

    //for (int i = 0; i < 32; i++) {
    //    stepSequencer.setProbability(i+1, 0);
    //}
    //stepSequencer.setProbability(0  + 1, 1);
    //stepSequencer.setProbability(8  + 1, 1);
    //stepSequencer.setProbability(16 + 1, 1);
    //stepSequencer.setProbability(24 + 1, 1);

    // Setup ofSound
    ofSoundStreamSettings settings;
    settings.setOutListener(this);
    settings.sampleRate = sampleRate;
    settings.numOutputChannels = 2;
    settings.numInputChannels = 0;
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);

    // Interaction Parameter
    mouseChaser.weight = 0.05f;
    knob1.setCenterPos(ofGetWidth() / 2.0f - 50, ofGetHeight() / 2.0f - 50);
    knob2.setCenterPos(ofGetWidth() / 2.0f + 50, ofGetHeight() / 2.0f - 50);
    knob3.setCenterPos(ofGetWidth() / 2.0f - 50, ofGetHeight() / 2.0f + 50);
    knob4.setCenterPos(ofGetWidth() / 2.0f + 50, ofGetHeight() / 2.0f + 50);

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

    drone1.setMasterVolume(pow(percentX, 1.4)* 0.8);
    drone2.setMasterVolume(pow(percentX, 1.4)* 0.8);

    knob1.update();
    knob2.update();
    knob3.update();
    knob4.update();

}

//--------------------------------------------------------------
void ofApp::draw(){

    // GUI : Mouse / Knob
    ofSetColor(ofColor::darkBlue);
    ofDrawCircle(mouseChaser.getPositionVec2(), 10);

    ofSetColor(ofColor::lightBlue);
    ofDrawCircle(mouseX, mouseY, 10);

    knob1.aim(mouseChaser.getPositionVec2());
    knob2.aim(mouseChaser.getPositionVec2());
    knob3.aim(mouseChaser.getPositionVec2());
    knob4.aim(mouseChaser.getPositionVec2());
    knob1.draw();
    knob2.draw();
    knob3.draw();
    knob4.draw();


    // Debug Values9
    ofDrawBitmapString("Mouse ( X , Y ) : " + to_string(mouseChaser.x) + " , " + to_string(mouseChaser.y), 20, 20);
    ofDrawBitmapString("Percentge ( X , Y ) : " + to_string(percentX) + " , " + to_string(percentY), 20, 40);

    ofDrawBitmapString("Pitch : " + to_string(pitch), 20, 60);

    ofDrawBitmapString("Knob1 Dir : "   + to_string(knob1.getDirection().x) + " , " + to_string(knob1.getDirection().y), 20, 80);
    ofDrawBitmapString("Knob1 Angle : " + to_string(knob1.getAngle()), 20, 100);
    ofDrawBitmapString("Knob1 Value : " + to_string(knob1.getAngularValue()), 20, 120);

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
        cout << "Fire : " << stepSequencer.getObservedNoteIndex() << " - " << ofGetElapsedTimef() << endl;
        std::size_t outChannels = output.getNumChannels();
        for (int i = 0; i < output.getNumFrames(); ++i) {

            vector<double> droneNote;
            droneNote.push_back(convert::mtof(69));
            droneNote.push_back(convert::mtof(73));
            droneNote.push_back(convert::mtof(76));
            droneNote.push_back(convert::mtof(80));
            droneNote.push_back(convert::mtof(83));


            output[i * outChannels]  = drone1.play(droneNote) * 0.2;
                for (int i=0; i<droneNote.size();i++){droneNote[i] *= pow(percentY, 0.6); }
            output[i * outChannels]  = drone2.play(droneNote) * 0.2;
            output[i * outChannels + 1] = output[i * outChannels];



            //Hold the values so the draw method can draw them
            waveform[waveIndex] = output[i * outChannels];
            if   (waveIndex < (ofGetWidth() - 1)) { ++waveIndex; }
            else { waveIndex = 0; }
        }
    //}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
