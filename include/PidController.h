#pragma once 
#include "raylib.h"

class PidController{
public:
    /*PidController(float newKp,float newKi,float newKd){
        error = 0;
        previousError = 0;
        proportional = 0;
        Kp = newKp;
        integral = 0;
        integralTerm = 0;
        Ki = newKi;
        Kd = newKd;
        output = 0;
        clampEnabled = false;
        minOuput = 0;
        maxOutput = 0;
    }*/

    float getKp() const { return Kp; }
    float getKi() const { return Ki; }
    float getKd() const { return Kd; }

    void setPidValues(){
        //P
        if(IsKeyPressed(KEY_T)){
            Kp -= 1.0;
        }
        if(IsKeyPressed(KEY_Y)){
            Kp += 1.0;
        }
        //I
        if(IsKeyPressed(KEY_G)){
            Ki -= 0.1;
        }
        if(IsKeyPressed(KEY_H)){
            Ki += 0.1;
        }
        //D
        if(IsKeyPressed(KEY_B)){
            Kd -= 0.1;
        }
        if(IsKeyPressed(KEY_N)){
            Kd += 0.1;
        }

        return;
   }

    void enableClamp(){
        clampEnabled = true;
    }

    void disableClamp(){
        clampEnabled = false;
    }

    void setOutputClamp(float min,float max){
        minOuput = min;
        maxOutput = max;
    }

    void fullReset(){
        error = 0;
        previousError = 0;
        proportional = 0;
        Kp = 0;
        integral = 0;
        integralTerm = 0;
        Ki = 0;
        Kd = 0;
        output = 0;
        clampEnabled = false;
        minOuput = 0;
        maxOutput = 0;
    }

    void reset(){
        error = 0;
        previousError = 0;
        proportional = 0;
        integral = 0;
        integralTerm = 0;
        output = 0;
        clampEnabled = false;
        minOuput = 0;
        maxOutput = 0;
    }

    void resetConstant(){
        Kp = 0;
        Ki = 0;
        Kd = 0;
    }

    void resetIntegral(){
        integral = 0;
    }

    float calculate(float setPoint,float targetPoint){
        error = targetPoint - setPoint;

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

        if(clampEnabled){
            if (output > maxOutput){
                output = maxOutput;
            }else if (output < minOuput) {
                output = minOuput;
            }    
        }    

        previousError = error;

        return output;
    }

private:
    float error;
    float previousError;
    float proportional;
    float Kp;
    float integral;
    float integralTerm;
    float Ki;
    float Kd;
    float output;
    bool clampEnabled;
    float minOuput;
    float maxOutput;
};
