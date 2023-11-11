#include "RadialKnob.h"

RadialKnob::RadialKnob() {
    RadialKnob(ofGetWidth() / 2, ofGetHeight() / 2);
}

RadialKnob::RadialKnob(int x, int y) {
    this->centerPos.x = x;
    this->centerPos.y = y;
}

glm::vec2 RadialKnob::getDirection() {
    return this->targetDir;
}

float RadialKnob::getAngle() {
    return this->angle;
}

float RadialKnob::getAngularValue() {
    return this->angularValue;
}

void RadialKnob::setCenterPos(glm::vec2 xy) {
    this->centerPos=xy;
}
void RadialKnob::setCenterPos(float x, float y) {
    this->centerPos = glm::vec2(x,y);
}


void RadialKnob::update() {
    angle = atan2(targetDir.y, targetDir.x)+PI;
    angularValue = angle/TAU;

}
void RadialKnob::draw() {



    // Fill
    ofFill();
    ofSetColor(240);;
    ofDrawCircle(centerPos, this->radius);

    // Outline
    ofSetColor(20);
    ofNoFill();
    ofDrawCircle(centerPos, this->radius);

    // Clock Hands
    ofSetColor(40);
    ofDrawLine(centerPos, targetDir * radius + centerPos);

}

void RadialKnob::aim(glm::vec2 targetPos) {
    this->targetPos = targetPos;
    this->targetDir = normalize(targetPos-centerPos);
}