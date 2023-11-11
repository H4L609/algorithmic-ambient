#pragma once
#include "ofMain.h"

class PositionChaser
{
public:
    PositionChaser();
    PositionChaser(glm::vec3 xyz, float weight);
    PositionChaser(glm::vec3 xyz);

    PositionChaser(glm::vec2 xy, float weight);
    PositionChaser(glm::vec2 xy);

    PositionChaser(float x, float weight);
    PositionChaser(float x);

    glm::vec3 getPositionVec3();
    glm::vec2 getPositionVec2();
    float     getPositionFloat();

    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float weight = 0.05f;

    void chase(glm::vec3 xyz);
    void chase(glm::vec2 xy);
    void chase(float     x);
};

