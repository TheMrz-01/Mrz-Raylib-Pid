#include "..\include\arms.h"
#include "..\include\motors.h"

//C
#include <stdio.h>
#include <math.h>

//C++
#include <iostream>
#include <cmath>

#define GRAVITY 9.8f

#define SCREENWIDTH 1024
#define SCREENHEIGHT 576

extern MechArm mechArm; 
extern Arm startArm;
extern Arm targetArm; 

typedef struct Button{
    Rectangle rect;
    Color color;
}Button;

typedef struct ButtonText{
    const char* text;
    float fontSize;
    Vector2 cords;
    Color color;
}ButtonText;

Button startButton = { 0 };
Button targetButton = { 0 };

Button moveButton = { 0 };
Button stopButton = { 0 };

ButtonText startButtonText = { 0 };
ButtonText targetButtonText = { 0 };

ButtonText moveButtonText = { 0 };
ButtonText stopButtonText = { 0 };

bool isAtStart = false;

const float damping = 0.1;

void setStartingPoint(Arm* refArm,Arm* arm,Button* button,ButtonText* text){
    if(IsMouseButtonDown(0) && (440 > GetMousePosition().x) && (GetMousePosition().x > 400) && (220 > GetMousePosition().y) && (GetMousePosition().y > 200)){
        button->color = MRZ_PRESSED_WHITE;
        text->color = MRZ_PRESSED_GRAY;
        arm->rotation = refArm->rotation;
    }
    else{
        button->color = MRZ_WHITE;
        text->color = MRZ_GRAY;    
    }
}

void setTargetPoint(Arm* refArm,Arm* arm,Button* button,ButtonText* text){
    if(IsMouseButtonDown(0) && (440 > GetMousePosition().x) && (GetMousePosition().x > 400) && (270 > GetMousePosition().y) && (GetMousePosition().y > 250)){
        button->color = MRZ_PRESSED_WHITE;
        text->color = MRZ_PRESSED_GRAY;
        arm->rotation = refArm->rotation;
    }
    else{
        button->color = MRZ_WHITE;
        text->color = MRZ_GRAY;    
    }
}

void isArmOkey(Arm* arm,Arm* startArm,Arm* targetArm,Button* stopButton,ButtonText* stopText,Button* moveButton,ButtonText* moveText){
    if(IsMouseButtonDown(0) && (635 > GetMousePosition().x) && (GetMousePosition().x > 580) && (370 > GetMousePosition().y) && (GetMousePosition().y > 350)){
        stopButton->color = MRZ_PRESSED_WHITE;
        stopText->color = MRZ_PRESSED_GRAY;
        //goForArm = false;
        arm->acceleration = 0;
        arm->velocity = 0;
    }
    else if(IsMouseButtonDown(0) && (515 > GetMousePosition().x) && (GetMousePosition().x > 460) && (370 > GetMousePosition().y) && (GetMousePosition().y > 350)){
        moveButton->color = MRZ_PRESSED_WHITE;
        moveText->color = MRZ_PRESSED_GRAY;
        arm->rotation = startArm->rotation;
        //goForArm = true;
        integral = 0;
        //previous_error = 0;
        //delete thi later
        previous_error = targetArm->rotation - arm->rotation;
    }
    else{
        moveButton->color = MRZ_WHITE;
        moveText->color = MRZ_GRAY;  
        stopButton->color = MRZ_WHITE;
        stopText->color = MRZ_GRAY;
    }
}

/*void applyGravity(Arm* arm){
    float angleInRadians = arm->rotation * (PI / 180.0f);
    float gravityTorque = GRAVITY * ARM_MASS * ARM_LENGTH * sin(angleInRadians) / 2;

    float gravitationalAcceleration = gravityTorque / (ARM_MASS * ARM_LENGTH * ARM_LENGTH / 3);
    arm->acceleration += gravitationalAcceleration;
}*/

/*void applyPhysics(Arm* arm){
    applyGravity(arm);

    arm->velocity += arm->acceleration * GetFrameTime();
    arm->velocity -= arm->velocity * damping * GetFrameTime();
    arm->rotation += arm->velocity * GetFrameTime();
}*/

/*void moveArm(Arm* arm,Arm* startArm,Arm* targetArm){
    error = targetArm->rotation - arm->rotation;
    proportional = error;
    integral += error * GetFrameTime();
    derivative = (error - previous_error) / GetFrameTime();
    output = arm->Kp * proportional + arm->Ki * integral  + arm->Kd * derivative;
    previous_error = error;
    //arm->rotation += output * GetFrameTime(); This will stay like this for some time
    //WaitTime(GetFrameTime());

    //Wait here lil ling ling
    arm->acceleration = output;
}*/

int main(void)
{
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Pid Controller");

    SetTargetFPS(60);

    //Start button
    startButton.rect = (Rectangle){400,200,40,20};
    startButton.color = MRZ_WHITE;

    //Target button
    targetButton.rect = (Rectangle){400,250,40,20};
    targetButton.color = MRZ_WHITE;

    //Start button text
    startButtonText.text = "Set";
    startButtonText.fontSize = 20;
    startButtonText.cords = (Vector2){startButton.rect.x + 1,startButton.rect.y};
    startButtonText.color = MRZ_GRAY;

    //Target button text
    targetButtonText.text = "Set";
    targetButtonText.fontSize = 20;
    targetButtonText.cords = (Vector2){targetButton.rect.x + 1,targetButton.rect.y};
    targetButtonText.color = MRZ_GRAY;

    //Move button 
    moveButton.rect = (Rectangle){460,350,55,20};
    moveButton.color = MRZ_WHITE;

    //Move button text
    moveButtonText.text = "Move";
    moveButtonText.fontSize = 20;
    moveButtonText.cords = (Vector2){moveButton.rect.x + 1,moveButton.rect.y};
    moveButtonText.color = MRZ_GRAY;

    //Stop button
    stopButton.rect = (Rectangle){580,350,55,20};
    stopButton.color = MRZ_WHITE;

    //Stop button text
    stopButtonText.text = "Stop";
    stopButtonText.fontSize = 20;
    stopButtonText.cords = (Vector2){stopButton.rect.x + 4,stopButton.rect.y};
    stopButtonText.color = MRZ_GRAY;

    printf("Hahahah\n");

    while (!WindowShouldClose())
    {
        mechArm.controlArm();
        mechArm.controlPIDValues();
        setStartingPoint(&mechArm,&startArm,&startButton,&startButtonText);
        setTargetPoint(&mechArm,&targetArm,&targetButton,&targetButtonText);
        isArmOkey(&mechArm,&startArm,&targetArm,&stopButton,&stopButtonText,&moveButton,&moveButtonText);

        if(mechArm.getGoForArm()){
            moveArm(&arm,&startPointArm,&targetPointArm);
            applyPhysics(&arm);
        }

        //Drawing shit goes here
        BeginDrawing();

            ClearBackground(MRZ_GRAY);

            DrawFPS(0,0);
    
            //Draw them arms
            mechArm.drawArm();
            startArm.drawArm();
            targetArm.drawArm();

            //Draw move button
            DrawRectangleRec(moveButton.rect,moveButton.color);
            DrawText(moveButtonText.text,moveButtonText.cords.x,moveButtonText.cords.y,moveButtonText.fontSize,moveButtonText.color);

            //Draw stop button
            DrawRectangleRec(stopButton.rect,stopButton.color);
            DrawText(stopButtonText.text,stopButtonText.cords.x,stopButtonText.cords.y,stopButtonText.fontSize,stopButtonText.color);

            //Draw arm shit
            char charRot[50];  
            sprintf(charRot, "%.2f", mechArm.getRotation());
            DrawText("Arm angle: ",450,150,20,MRZ_WHITE);
            DrawText(charRot,450 + 130,150,20,MRZ_WHITE);

            //Draw them target arm shit
            char charStartRot[50];  
            sprintf(charStartRot, "%.2f", startArm.getRotation());
            DrawText("Starting arm angle: ",startButton.rect.x + 50,startButton.rect.y,targetButtonText.fontSize,MRZ_WHITE);
            DrawText(charStartRot,startButton.rect.x + 50 + 200,startButton.rect.y,targetButtonText.fontSize,MRZ_WHITE);

            DrawRectangleRec(targetButton.rect,targetButton.color);
            DrawText(targetButtonText.text,targetButtonText.cords.x,targetButtonText.cords.y,targetButtonText.fontSize,targetButtonText.color);
            
            //Draw them starting arm shit
            char charTargetRot[50];  
            sprintf(charTargetRot, "%.2f",targetArm.getRotation());
            DrawText("Target arm angle: ",targetButton.rect.x + 50,targetButton.rect.y,startButtonText.fontSize,MRZ_WHITE);
            DrawText(charTargetRot,targetButton.rect.x + 50 + 200,targetButton.rect.y,startButtonText.fontSize,MRZ_WHITE);

            DrawRectangleRec(startButton.rect,startButton.color);
            DrawText(startButtonText.text,startButtonText.cords.x,startButtonText.cords.y,startButtonText.fontSize,startButtonText.color);

            //PID Values
            char charPValue[50];  
            sprintf(charPValue, "%.2f",mechArm.getKp());
            DrawText("P: ",400,420,20,MRZ_WHITE);
            DrawText(charPValue,400+20,420,20,MRZ_WHITE);

            char charIValue[50];  
            sprintf(charIValue, "%.2f",mechArm.getKi());
            DrawText("I: ",525,420,20,MRZ_WHITE);
            DrawText(charIValue,525+20,420,20,MRZ_WHITE);

            char charDValue[50];  
            sprintf(charDValue, "%.2f",mechArm.getKd());
            DrawText("D: ",635,420,20,MRZ_WHITE);
            DrawText(charDValue,635+20,420,20,MRZ_WHITE);

            DrawText("Press T-Y for P, G-H for I, B-N for D",350,470,20,MRZ_WHITE);

        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}