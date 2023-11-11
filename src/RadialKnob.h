#pragma once

#include "ofMain.h"

class RadialKnob // 2D
{
public:
    RadialKnob();
    RadialKnob(int x, int y);
    void update();
    void draw();

    const float TAU = TWO_PI;

    glm::vec2 getDirection();
    float getAngle();
    float getAngularValue();

    void setCenterPos(glm::vec2 xy);
    void setCenterPos(float x, float y);

    void aim(glm::vec2 targetPos);

    //void updateAngle(); // targetDir �� centerx,y ���g���Ċp�x�����߂�
    //void setAngle(); // �p�x��^����ƁAtargetDir�������ς��

private:
    // Draw Parameter
    float radius = 30;

    glm::vec2 centerPos;
    glm::vec2 targetPos;
    glm::vec2 targetDir;

    // Value
    float angle        = 0;
    float angularValue = 0;


    //void rotate(glm::vec2 targetPos);
    //void rotate(float targetx , float targety);

};

