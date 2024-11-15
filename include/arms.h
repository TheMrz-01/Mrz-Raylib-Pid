#pragma once
#include "motors.h"
#include "mrzColors.h"
#include <iostream>
#include <cmath>

extern Motor Falcon500;
extern Motor KarkenX60;

const float damping = 0.1f;

class Arm{
public:
    Arm(const Rectangle& rect, const Vector2& origin, float rotation, const Color& color)
        : origin(origin), rotation(rotation), color(color), rect(rect) {}

    // Getters
    Vector2 getOrigin() const { return origin; }
    float getRotation() const { return rotation; }
    Color getColor() const { return color; }
    Rectangle getRect() const { return rect; }

    // Setters
    void setOrigin(const Vector2& newOrigin) { origin = newOrigin; }
    void setRotation(float newRotation) { rotation = newRotation; }
    void setColor(const Color& newColor) { color = newColor; }
    void setRect(const Rectangle& newRect) { rect = newRect; }

    void drawArm() const {
        DrawRectanglePro(rect, origin, rotation, color);
    }

protected:
    //Raylib stuff
    Rectangle rect;
    Vector2 origin;
    float rotation;
    Color color;
};

class MechArm : public Arm{
public:
    MechArm(const Rectangle& rect, const Vector2& origin,float rotation, const Color& color, float speed, 
        float mass, float length, float acceleration, float velocity, float kp, float ki, float kd, 
        float previousError,float integral,float error,float proportional,float derivative,float output,int goForArm)
        : Arm(rect, origin, rotation, color), speed(speed), acceleration(acceleration)
        ,velocity(velocity), mass(mass), length(length), Kp(kp), Ki(ki), Kd(kd),previousError(previousError),
        integral(integral), error(error), proportional(proportional), derivative(derivative),
        output(output), goForArm(goForArm){}

    //Getters
    
    //Raylib
    Vector2 getOrigin() const { return origin; }
    float getRotation() const { return rotation; }
    Color getColor() const { return color; }
    Rectangle getRect() const { return rect; }

    //Physics
    float getSpeed() const { return speed; }
    float getMass() const { return mass; }
    float getLength() const { return length; }
    float getAcceleration() const { return acceleration; }
    float getVelocity() const { return velocity; }

    //Pid
    float getKp() const { return Kp; }
    float getKi() const { return Ki; }
    float getKd() const { return Kd; }
    float getPreviousError() const { return previousError; }
    float getIntegral() const { return integral; }
    float getError() const { return error; }
    float getProportional() const { return proportional; }
    float getDerivative() const { return derivative; }
    float getOutput() const { return output; }

    //Nuh uh.I'm gonna do IT!
    int getGoForArm() const { return goForArm; }

    // Setters

    //Raylib
    void setOrigin(const Vector2& newOrigin) { origin = newOrigin; }
    void setRotation(float newRotation) { rotation = newRotation; }
    void setColor(const Color& newColor) { color = newColor; }
    void setRect(const Rectangle& newRect) { rect = newRect; }

    //Physics
    void setSpeed(float newSpeed) { speed = newSpeed; }
    void setMass(float newMass) { mass = newMass; }
    void setLength(float newLength) { length = newLength; }
    void setAcceleration(float newAcceleration) { acceleration = newAcceleration; }
    void setVelocity(float newVelocity) { velocity = newVelocity; }
    
    //Pid
    void setKp(float newKp) { Kp = newKp; }
    void setKi(float newKi) { Ki = newKi; }
    void setKd(float newKd) { Kd = newKd; }
    void setPreviousError(float newPreviousError) { previousError = newPreviousError; }
    void setIntegral(float newIntegral) { integral = newIntegral; }
    void setError(float newError) { error = newError; }
    void setProportional(float newProportional) { proportional = newProportional; }
    void setDerivative(float newDerivative) { derivative = newDerivative; }
    void setOutput(float newOutput) { output = newOutput; }

    //Nuh uh.I'm gonna do IT!
    void setGoForArm(int newGoForArm) { goForArm = newGoForArm; }

    void drawArm() const {
        DrawRectanglePro(rect, origin, rotation, color);
    }
    void controlArm();
    void controlPIDValues();
    void applyGravity();
    void applyPhysics();
    void moveArm(Arm* targetArm,Motor* motor);

private:
    //Raylib stuff
    float speed;
    //Physics
    float mass;
    float length;
    float acceleration;
    float velocity;
    //Pid
    float Kp;
    float Ki;
    float Kd;
    float previousError;
    float integral;
    float error;
    float proportional;
    float derivative;
    float output;
    //Other
    int goForArm;
};