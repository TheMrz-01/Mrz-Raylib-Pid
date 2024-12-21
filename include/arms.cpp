#include "arms.h"
#include "motors.h"

#include <stdio.h>

extern Motor selectedMotor;

//Start arm vars
Rectangle startRect = {200,225,2*2,80*2};
Vector2 startOrigin = {startRect.width / 2, 0};
Color startColor = MRZ_DEBUG_YELLOW;
float startRotation = 0.0f;

//Target arm vars
Rectangle targetRect = {200,225,2*2,80*2};
Vector2 targetOrigin = {targetRect.width / 2, 0};
Color targetColor = MRZ_DEBUG_ORANGE;
float targetRotation = 180.0f;

//Mechanical arm vars
Rectangle rect = {200,225,2*2,80*2};
Vector2 origin = {rect.width / 2, 0};
Color color = MRZ_RED_ORANGE;
float rotation = 90.0f;
float speed = 100.0f;
float mass = 1.0f;
float length = (float)(rect.width); //Keep an eye on this one
float I = (1.0 / 3.0) * mass * length * length;
float gravityTorque = 0;
float totalTorque = 0;
float angularAcceleration = 0;
float angularVelocity = 0;
int goForArm = 0;

Arm startArm(startRect,startOrigin,startRotation,startColor);
Arm targetArm(targetRect,targetOrigin,targetRotation,targetColor);
MechArm mechArm(rect,origin,rotation,color,speed,mass,length,angularAcceleration,angularVelocity,goForArm);

void MechArm::controlArm(){
    if(mechArm.getGoForArm())
        return;

    if (IsKeyDown(KEY_UP)){
        setRotation(getRotation() + getSpeed() * GetFrameTime());
    }
    if (IsKeyDown(KEY_DOWN)){
        setRotation(getRotation() - getSpeed() * GetFrameTime());
    }

    return;
}

void MechArm::reset(){
    angularAcceleration = 0;
    angularVelocity = 0;
    totalTorque = 0;
}

void MechArm::applyGravity(){
    gravityTorque = -mass * GRAVITY * (length / 2.0) * sin(rotation);
    totalTorque = gravityTorque + selectedMotor.calculateTorque();
    angularAcceleration = totalTorque / I;
    angularVelocity += angularAcceleration * GetFrameTime() + selectedMotor.calculateSpeed();

    rotation += angularVelocity * GetFrameTime();

    //Some resistance or friction stuff idk

    angularVelocity *= damping;

    return;
}

void MechArm::applyPhysics(){
    applyGravity();

    return;
}

