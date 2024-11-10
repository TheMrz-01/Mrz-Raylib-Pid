#include "include/raylib.h"
#include <stdio.h>
#include <math.h>

#define SCREENWIDTH 1024
#define SCREENHEIGHT 576

#define MRZ_WHITE (Color){255, 255, 255, 255}
#define MRZ_PRESSED_WHITE (Color){200, 200, 200, 255}
#define MRZ_GRAY (Color){43, 43, 43, 255}
#define MRZ_PRESSED_GRAY (Color){23, 23, 23, 255}
#define MRZ_RED_ORANGE (Color){252, 65, 3, 255}
#define MRZ_DEBUG_ORANGE (Color){252, 90, 3, 100}
#define MRZ_DEBUG_YELLOW (Color){252, 165, 3, 100}

#define GRAVITY 9.8f
#define ARM_MASS 1.0f
#define ARM_LENGTH 80.0f 

typedef struct Arm{
    Vector2 origin;
    float speed;
    float rotation;
    Color color;
    Rectangle rect;
    float velocity;
    float acceleration;
    float Kp;
    float Ki;
    float Kd;
}Arm;

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

Arm arm = { 0 };
Arm startPointArm = { 0 };
Arm targetPointArm = { 0 };

Button startButton = { 0 };
Button targetButton = { 0 };

Button moveButton = { 0 };
Button stopButton = { 0 };

ButtonText startButtonText = { 0 };
ButtonText targetButtonText = { 0 };

ButtonText moveButtonText = { 0 };
ButtonText stopButtonText = { 0 };

bool goForArm = false;
bool isAtStart = false;

const float damping = 0.1;

//PID stuff
float previous_error = 0;
float integral = 0;
float error = 0;
float proportional = 0;
float derivative = 0;
float output = 0;

void controlArmPos(Arm* arm){
    if(goForArm)
        return;

    // && (arm->rotation < 179.05)  && (arm->rotation > 0)
    if (IsKeyDown(KEY_UP)){
        arm->rotation += arm->speed * GetFrameTime();
    }
    if (IsKeyDown(KEY_DOWN)){
        arm->rotation -= arm->speed * GetFrameTime();
    }

    return;
}

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

int isArmOkey(Arm* arm,Arm* startArm,Arm* targetArm,Button* stopButton,ButtonText* stopText,Button* moveButton,ButtonText* moveText){
    if(IsMouseButtonDown(0) && (635 > GetMousePosition().x) && (GetMousePosition().x > 580) && (370 > GetMousePosition().y) && (GetMousePosition().y > 350)){
        stopButton->color = MRZ_PRESSED_WHITE;
        stopText->color = MRZ_PRESSED_GRAY;
        goForArm = false;
        arm->acceleration = 0;
        arm->velocity = 0;
    }
    else if(IsMouseButtonDown(0) && (515 > GetMousePosition().x) && (GetMousePosition().x > 460) && (370 > GetMousePosition().y) && (GetMousePosition().y > 350)){
        moveButton->color = MRZ_PRESSED_WHITE;
        moveText->color = MRZ_PRESSED_GRAY;
        arm->rotation = startArm->rotation;
        goForArm = true;
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

void applyGravity(Arm* arm){
    float angleInRadians = arm->rotation * (PI / 180.0f);
    float gravityTorque = GRAVITY * ARM_MASS * ARM_LENGTH * sin(angleInRadians) / 2;

    float gravitationalAcceleration = gravityTorque / (ARM_MASS * ARM_LENGTH * ARM_LENGTH / 3);
    arm->acceleration += gravitationalAcceleration;
}

void applyPhysics(Arm* arm){
    applyGravity(&arm);

    arm->velocity += arm->acceleration * GetFrameTime();
    arm->velocity -= arm->velocity * damping * GetFrameTime();
    arm->rotation += arm->velocity * GetFrameTime();
}

void moveArm(Arm* arm,Arm* startArm,Arm* targetArm){
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
}

int main(void)
{
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Pid Controller");
    SetTargetFPS(60);

    //Normal Arm Thingy
    arm.speed = 100.0;
    arm.rotation = 90.0;
    arm.color = MRZ_RED_ORANGE;
    arm.rect = (Rectangle){200,225,2*2,80*2};
    arm.origin = (Vector2){arm.rect.width / 2,0};
    //Physics
    arm.velocity = 0.0;
    arm.acceleration = 0.0;
    //PID Values
    arm.Kp = 10.0;
    arm.Ki = 0.1;
    arm.Kd = 1.0;
    
    //Start Arm Thingy
    startPointArm.speed = 100.0;
    startPointArm.rotation = 0.0;
    startPointArm.color = MRZ_DEBUG_ORANGE;
    startPointArm.rect = (Rectangle){200,225,2*2,80*2};
    startPointArm.origin = (Vector2){startPointArm.rect.width / 2,0};

    //Target Arm Thingy
    targetPointArm.speed = 100.0;
    targetPointArm.rotation = 180.0;
    targetPointArm.color = MRZ_DEBUG_YELLOW;
    targetPointArm.rect = (Rectangle){200,225,2*2,80*2};
    targetPointArm.origin = (Vector2){targetPointArm.rect.width / 2,0};

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

    while (!WindowShouldClose())
    {
        controlArmPos(&arm);
        setStartingPoint(&arm,&startPointArm,&startButton,&startButtonText);
        setTargetPoint(&arm,&targetPointArm,&targetButton,&targetButtonText);
        isArmOkey(&arm,&startPointArm,&targetPointArm,&stopButton,&stopButtonText,&moveButton,&moveButtonText);

        if(goForArm){
            moveArm(&arm,&startPointArm,&targetPointArm);
        }

        applyPhysics(&arm);

        //Drawing shit goes here
        BeginDrawing();

            ClearBackground(MRZ_GRAY);
    
            //Draw them arms
            DrawRectanglePro(arm.rect,arm.origin,arm.rotation,arm.color);
            DrawRectanglePro(startPointArm.rect,startPointArm.origin,startPointArm.rotation,startPointArm.color);
            DrawRectanglePro(targetPointArm.rect,targetPointArm.origin,targetPointArm.rotation,targetPointArm.color);

            //Draw move button
            DrawRectangleRec(moveButton.rect,moveButton.color);
            DrawText(moveButtonText.text,moveButtonText.cords.x,moveButtonText.cords.y,moveButtonText.fontSize,moveButtonText.color);

            //Draw stop button
            DrawRectangleRec(stopButton.rect,stopButton.color);
            DrawText(stopButtonText.text,stopButtonText.cords.x,stopButtonText.cords.y,stopButtonText.fontSize,stopButtonText.color);

            //Draw arm shit
            char charRot[50];  
            sprintf(charRot, "%.2f", arm.rotation);
            DrawText("Arm angle: ",450,150,20,MRZ_WHITE);
            DrawText(charRot,450 + 130,150,20,MRZ_WHITE);

            //Draw them target arm shit
            char charStartRot[50];  
            sprintf(charStartRot, "%.2f", startPointArm.rotation);
            DrawText("Starting arm angle: ",startButton.rect.x + 50,startButton.rect.y,targetButtonText.fontSize,MRZ_WHITE);
            DrawText(charStartRot,startButton.rect.x + 50 + 200,startButton.rect.y,targetButtonText.fontSize,MRZ_WHITE);

            DrawRectangleRec(targetButton.rect,targetButton.color);
            DrawText(targetButtonText.text,targetButtonText.cords.x,targetButtonText.cords.y,targetButtonText.fontSize,targetButtonText.color);
            
            //Draw them starting arm shit
            char charTargetRot[50];  
            sprintf(charTargetRot, "%.2f",targetPointArm.rotation);
            DrawText("Target arm angle: ",targetButton.rect.x + 50,targetButton.rect.y,startButtonText.fontSize,MRZ_WHITE);
            DrawText(charTargetRot,targetButton.rect.x + 50 + 200,targetButton.rect.y,startButtonText.fontSize,MRZ_WHITE);

            DrawRectangleRec(startButton.rect,startButton.color);
            DrawText(startButtonText.text,startButtonText.cords.x,startButtonText.cords.y,startButtonText.fontSize,startButtonText.color);

        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}