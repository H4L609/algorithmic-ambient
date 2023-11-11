#include "RadialKnob.h"

RadialKnob::RadialKnob() {
    RadialKnob(ofGetWidth() / 2, ofGetHeight() / 2);
}

RadialKnob::RadialKnob(int x, int y) {
    this->centerPos.x = x;
    this->centerPos.y = y;
    bool isActive=true;
}

glm::vec2 RadialKnob::getDirection() {
    return this->aimTargetDir;
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
    angle = atan2(aimTargetDir.y, aimTargetDir.x)+PI;
    angularValue = angle/TAU;

}
void RadialKnob::draw() {

    // Fill
    ofFill();
    ofSetColor(240 * (int)isActive + 100 * (int)!isActive); // Activeじゃないとき暗くなる。
    ofDrawCircle(centerPos, this->radius);

    // Outline
    ofSetColor(20);
    ofNoFill();
    ofDrawCircle(centerPos, this->radius);

    // Clock Hands
    ofSetColor(40);
    ofDrawLine(centerPos, aimTargetDir * radius + centerPos);

}

void RadialKnob::ON() {
    this->isActive=true;
}
void RadialKnob::OFF() {
    this->isActive=false;
}

void RadialKnob::aim(glm::vec2 targetPos) {
    this->aimTargetPos = (int)isActive * targetPos + (int)!isActive * this->aimTargetPos;
    this->aimTargetDir.x = ofLerp(aimTargetDir.x, normalize(this->aimTargetPos - centerPos).x, aimWeight); // イージング
    this->aimTargetDir.y = ofLerp(aimTargetDir.y, normalize(this->aimTargetPos - centerPos).y, aimWeight); // イージング
}