#include "..\include\arms.h"
#include "..\include\motors.h"
#include "..\include\mrzUtils.h"
#include "..\include\PidController.h"

//[TODO]
//Add option to change the motor that is in use

//C
#include <stdio.h>
#include <math.h>

//C++
#include <iostream>
#include <cmath>

#define SCREENWIDTH 1024
#define SCREENHEIGHT 576

extern MechArm mechArm; 
extern Arm startArm;
extern Arm targetArm; 

extern Motor selectedMotor;

PidController pidController = PidController();

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

void setStartingPoint(Button* button,ButtonText* text){
    if(IsMouseButtonDown(0) && (440 > GetMousePosition().x) && (GetMousePosition().x > 400) && (220 > GetMousePosition().y) && (GetMousePosition().y > 200)){
        button->color = MRZ_PRESSED_WHITE;
        text->color = MRZ_PRESSED_GRAY;
        startArm.setRotation(mechArm.getRotation());
    }
    else{
        button->color = MRZ_WHITE;
        text->color = MRZ_GRAY;    
    }
}

void setTargetPoint(Button* button,ButtonText* text){
    if(IsMouseButtonDown(0) && (440 > GetMousePosition().x) && (GetMousePosition().x > 400) && (270 > GetMousePosition().y) && (GetMousePosition().y > 250)){
        button->color = MRZ_PRESSED_WHITE;
        text->color = MRZ_PRESSED_GRAY;
        targetArm.setRotation(mechArm.getRotation());
    }
    else{
        button->color = MRZ_WHITE;
        text->color = MRZ_GRAY;    
    }
}

void isArmOkey(Button* stopButton,ButtonText* stopText,Button* moveButton,ButtonText* moveText){
    if(IsMouseButtonDown(0) && (635 > GetMousePosition().x) && (GetMousePosition().x > 580) && (370 > GetMousePosition().y) && (GetMousePosition().y > 350)){
        stopButton->color = MRZ_PRESSED_WHITE;
        stopText->color = MRZ_PRESSED_GRAY;
        mechArm.setGoForArm(0);
        mechArm.reset();
        selectedMotor.breaker();
        selectedMotor.reset();
    }
    else if(IsMouseButtonDown(0) && (515 > GetMousePosition().x) && (GetMousePosition().x > 460) && (370 > GetMousePosition().y) && (GetMousePosition().y > 350)){
        moveButton->color = MRZ_PRESSED_WHITE;
        moveText->color = MRZ_PRESSED_GRAY;
        mechArm.reset();
        mechArm.setRotation(startArm.getRotation());
        mechArm.setGoForArm(1);
        //previous_error = 0;
        //delete thi later
        
    }
    else{
        moveButton->color = MRZ_WHITE;
        moveText->color = MRZ_GRAY;  
        stopButton->color = MRZ_WHITE;
        stopText->color = MRZ_GRAY;
    }
}

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

    pidController.reset();
    pidController.enableClamp();
    pidController.setOutputClamp(0,12);

    while (!WindowShouldClose())
    {
        mechArm.controlArm();
        pidController.setPidValues();
        setStartingPoint(&startButton,&startButtonText);
        setTargetPoint(&targetButton,&targetButtonText);
        isArmOkey(&stopButton,&stopButtonText,&moveButton,&moveButtonText);

        if(mechArm.getGoForArm()){
            mechArm.applyPhysics();
            float output = pidController.calculate(mechArm.getRotation(),targetArm.getRotation());
            selectedMotor.setVoltage(output);
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
            sprintf(charPValue, "%.2f",pidController.getKp());
            DrawText("P: ",400,420,20,MRZ_WHITE);
            DrawText(charPValue,400+20,420,20,MRZ_WHITE);

            char charIValue[50];  
            sprintf(charIValue, "%.2f",pidController.getKi());
            DrawText("I: ",525,420,20,MRZ_WHITE);
            DrawText(charIValue,525+20,420,20,MRZ_WHITE);

            char charDValue[50];  
            sprintf(charDValue, "%.2f",pidController.getKd());
            DrawText("D: ",635,420,20,MRZ_WHITE);
            DrawText(charDValue,635+20,420,20,MRZ_WHITE);

            DrawText("Press -> T-Y for P || G-H for I || B-N for D",350,470,20,MRZ_WHITE);

        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}