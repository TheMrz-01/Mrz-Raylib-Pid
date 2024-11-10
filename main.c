#include "include/raylib.h"
#include <stdio.h>
#include <math.h>

#define SCREENWIDTH 800
#define SCREENHEIGHT 450

#define MRZ_WHITE (Color){255, 255, 255, 255}
#define MRZ_PRESSED_WHITE (Color){200, 200, 200, 255}
#define MRZ_GRAY (Color){43, 43, 43, 255}
#define MRZ_PRESSED_GRAY (Color){23, 23, 23, 255}
#define MRZ_RED_ORANGE (Color){252, 65, 3, 255}
#define MRZ_DEBUG_ORANGE (Color){252, 90, 3, 100}
#define MRZ_DEBUG_YELLOW (Color){252, 165, 3, 100}

typedef struct Arm{
    Vector2 origin;
    float speed;
    float rotation;
    Color color;
    Rectangle rect;
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

void controlArmPos(Arm* arm){
    if((arm->rotation > 180)){
        arm->rotation = 180;
    }
    else if(arm->rotation < 0){
        arm->rotation = 0;
    }

    // && (arm->rotation < 179.05)  && (arm->rotation > 0)
    if (IsKeyDown(KEY_UP) && (arm->rotation < 179.05)){
        arm->rotation += arm->speed * GetFrameTime();
        printf("LEFT\n");
    }
    if (IsKeyDown(KEY_DOWN) && (arm->rotation > 0)){
        arm->rotation -= arm->speed * GetFrameTime();
        printf("Right\n");
    }

    return;
}

void setStartingPoint(Arm* refArm,Arm* arm,Button* button,ButtonText* text){
    if(IsMouseButtonDown(0) && (440 > GetMousePosition().x) && (GetMousePosition().x > 400) && (220 > GetMousePosition().y) && (GetMousePosition().y > 200)){
        button->color = MRZ_PRESSED_WHITE;
        text->color = MRZ_PRESSED_GRAY;
        arm->rotation = refArm->rotation;
        printf("Start");
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
        printf("Target");
    }
    else{
        button->color = MRZ_WHITE;
        text->color = MRZ_GRAY;    
    }
}

int isArmOkey(Button* stopButton,ButtonText* stopText,Button* moveButton,ButtonText* moveText){
    if(IsMouseButtonDown(0) && (635 > GetMousePosition().x) && (GetMousePosition().x > 580) && (370 > GetMousePosition().y) && (GetMousePosition().y > 350)){
        stopButton->color = MRZ_PRESSED_WHITE;
        stopText->color = MRZ_PRESSED_GRAY;
        goForArm = false;
        printf("stop");
    }
    else if(IsMouseButtonDown(0) && (515 > GetMousePosition().x) && (GetMousePosition().x > 460) && (370 > GetMousePosition().y) && (GetMousePosition().y > 350)){
        moveButton->color = MRZ_PRESSED_WHITE;
        moveText->color = MRZ_PRESSED_GRAY;
        goForArm = true;
        printf("move");
    }
    else{
        moveButton->color = MRZ_WHITE;
        moveText->color = MRZ_GRAY;  
        stopButton->color = MRZ_WHITE;
        stopText->color = MRZ_GRAY;   
    }
}

int moveArm(){
    

    return 1;
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
    //PID Values
    arm.Kp = 10;
    arm.Ki = 0;
    arm.Kd = 0;
    
    //Start Arm Thingy
    startPointArm.speed = 100.0;
    startPointArm.rotation = 180.0;
    startPointArm.color = MRZ_DEBUG_ORANGE;
    startPointArm.rect = (Rectangle){200,225,2*2,80*2};
    startPointArm.origin = (Vector2){startPointArm.rect.width / 2,0};

    //Target Arm Thingy
    targetPointArm.speed = 100.0;
    targetPointArm.rotation = 0.0;
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
        isArmOkey(&stopButton,&stopButtonText,&moveButton,&moveButtonText);

        if(goForArm){
            moveArm();
        }

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