#pragma once

#include "ofMain.h"
#include "PositionChaser.h"

class RadialKnob // 2D
{
public:
    RadialKnob();
    RadialKnob(int x, int y);
    void update();
    void draw();

    const float TAU = TWO_PI;

    glm::vec2 getDirection();
    float     getAngle();
    float     getAngularValue();

    void setCenterPos(glm::vec2 xy);
    void setCenterPos(float x, float y);

    void ON();
    void OFF();

    void aim(glm::vec2 targetPos);

    //void updateAngle(); // targetDir と centerx,y を使って角度を求める
    //void setAngle(); // 角度を与えると、targetDirが書き変わる

private:
    // Draw Parameter
    float radius = 30;

    // Vector Variables
    glm::vec2 centerPos;
    glm::vec2 aimTargetPos;
    glm::vec2 aimTargetDir;

    // Easing
    float aimWeight=0.05;

    // Value
    float angle        = 0;
    float angularValue = 0;

    // Active Status
    bool isActive;


    //void rotate(glm::vec2 targetPos);
    //void rotate(float targetx , float targety);

};

