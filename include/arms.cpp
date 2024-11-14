#include "arms.h"

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
float Kp = 10.0f;
float Ki = 0.1f;
float Kd = 1.0f;
int goForArm = 0;

Arm startArm(startRect,startOrigin,startRotation,startColor);
Arm targetArm(targetRect,targetOrigin,targetRotation,targetColor);
MechArm mechArm(rect,origin,rotation,color,speed,mass,length,Kp,Ki,Kd,goForArm);

void MechArm::controlArm(){
    if(mechArm.getGoForArm())
        return;

    if (IsKeyDown(KEY_UP)){
        mechArm.setRotation(mechArm.getRotation() + mechArm.getSpeed() * GetFrameTime());
    }
    if (IsKeyDown(KEY_DOWN)){
        mechArm.setRotation(mechArm.getRotation() - mechArm.getSpeed() * GetFrameTime());
    }

    return;
}

void MechArm::controlPIDValues(){
    //P
    if(IsKeyPressed(KEY_T)){
        mechArm.setKp(mechArm.getKp() - 1);
    }
    if(IsKeyPressed(KEY_Y)){
        mechArm.setKp(mechArm.getKp() + 1);
    }
    //I
    if(IsKeyPressed(KEY_G)){
        mechArm.setKp(mechArm.getKi() - 1);
    }
    if(IsKeyPressed(KEY_H)){
        mechArm.setKp(mechArm.getKi() + 1);
    }
    //D
    if(IsKeyPressed(KEY_B)){
        mechArm.setKp(mechArm.getKd() - 1);
    }
    if(IsKeyPressed(KEY_N)){
        mechArm.setKp(mechArm.getKd() + 1);
    }

    return;
}

int main(void){
    return 0;
}