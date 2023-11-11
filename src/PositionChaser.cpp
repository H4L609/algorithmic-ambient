#include "PositionChaser.h"

PositionChaser::PositionChaser(){}

PositionChaser::PositionChaser(glm::vec3 xyz, float weight) {
    this->x      = xyz.x;
    this->y      = xyz.y;
    this->z      = xyz.z;
    this->weight = weight;
}
PositionChaser::PositionChaser(glm::vec3 xyz) {
    PositionChaser(xyz, weight);
}

PositionChaser::PositionChaser(glm::vec2 xy, float weight) {
    this->x = xy.x;
    this->y = xy.y;
    this->weight = weight;
}
PositionChaser::PositionChaser(glm::vec2 xy) {
    PositionChaser(xy, weight);
}

PositionChaser::PositionChaser(float x, float weight) {
    this->x = x;
    this->weight=weight;
}
PositionChaser::PositionChaser(float x) {
    PositionChaser(x, weight);
}

glm::vec3 PositionChaser::getPositionVec3() {
    return glm::vec3(this->x, this->y, this->z);
}
glm::vec2 PositionChaser::getPositionVec2() {
    return glm::vec2(this->x, this->y);
}
float PositionChaser::getPositionFloat() {
    return x;
}


void PositionChaser::chase(glm::vec3 xyz) {
    this->x = ofLerp(this->x, xyz.x, weight);
    this->y = ofLerp(this->y, xyz.y, weight);
    this->z = ofLerp(this->z, xyz.z, weight);
}
void PositionChaser::chase(glm::vec2 xy) {
    this->x = ofLerp(this->x, xy.x, weight);
    this->y = ofLerp(this->y, xy.y, weight);

}
void PositionChaser::chase(float x) {
    this->x = ofLerp(this->x, x, weight);
}