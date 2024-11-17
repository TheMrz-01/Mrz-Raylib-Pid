#include "arms.h"
#include "motors.h"

extern Motor Falcon500;
extern Motor KarkenX60;

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
float acceleration = 0;
float velocity = 0;
float Kp = 10.0f;
float Ki = 0.1f;
float Kd = 1.0f;
float previousError = 0;
float integral = 0;
float error = 0;
float proportional = 0;
float derivative = 0;
float output = 0;
int goForArm = 0;

Arm startArm(startRect,startOrigin,startRotation,startColor);
Arm targetArm(targetRect,targetOrigin,targetRotation,targetColor);
MechArm mechArm(rect,origin,rotation,color,speed,mass,length,acceleration,velocity,
Kp,Ki,Kd,previousError,integral,error,proportional,derivative,output,goForArm);

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

void MechArm::controlPIDValues(){
    //P
    if(IsKeyPressed(KEY_T)){
        mechArm.setKp(mechArm.getKp() - 1.0);
    }
    if(IsKeyPressed(KEY_Y)){
        mechArm.setKp(mechArm.getKp() + 1.0);
    }
    //I
    if(IsKeyPressed(KEY_G)){
        mechArm.setKi(mechArm.getKi() - 0.1);
    }
    if(IsKeyPressed(KEY_H)){
        mechArm.setKi(mechArm.getKi() + 0.1);
    }
    //D
    if(IsKeyPressed(KEY_B)){
        mechArm.setKd(mechArm.getKd() - 0.1);
    }
    if(IsKeyPressed(KEY_N)){
        mechArm.setKd(mechArm.getKd() + 0.1);
    }

    return;
}

void MechArm::applyGravity(){
    float angleInRadians = rotation * (PI / 180.0f);
    float gravityTorque = gravity * mass * length * sin(angleInRadians) / 2;

    float gravitationalAcceleration = gravityTorque / (mass * length * length / 3);
    acceleration += gravitationalAcceleration;

    return;
}

void MechArm::applyPhysics(){
    applyGravity();

    velocity += acceleration * GetFrameTime();
    velocity -= velocity * damping * GetFrameTime();
    rotation += velocity * GetFrameTime();

    return;
}

void MechArm::moveArm(Arm* targetArm,Motor* motor){
    error = targetArm->getRotation() - rotation;

    //proportional = error;
    float proportional = Kp * error;

    //integral += error * GetFrameTime();
    integral += error * GetFrameTime();
    float integralTerm = Ki * integral;

    //derivative = (error - previousError) / GetFrameTime();
    float derivative = (error - previousError) / GetFrameTime();
    float derivativeTerm = Kd * derivative;

    //output = Kp * proportional + Ki * integral  + Kd * derivative;
    float outputVoltage = proportional + integralTerm + derivativeTerm;

    if (outputVoltage > motor->getMaxVoltage()){
        outputVoltage = motor->getMaxVoltage();
    } else if (outputVoltage < motor->getMinVoltage()) {
        outputVoltage = motor->getMinVoltage();
    }

    previousError = error;

    motor->setAppliedVoltage(outputVoltage);

    return;
}
