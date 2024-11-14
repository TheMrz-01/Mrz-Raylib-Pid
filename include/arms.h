#pragma once

#include "raylib.h"
#include "mrzColors.h"
#include <iostream>

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
        float mass, float length, float kp, float ki, float kd, int goForArm)
        : Arm(rect, origin, rotation, color), speed(speed),
        mass(mass), length(length), Kp(kp), Ki(ki), Kd(kd), goForArm(goForArm){}

    //Getters
    Vector2 getOrigin() const { return origin; }
    float getRotation() const { return rotation; }
    Color getColor() const { return color; }
    Rectangle getRect() const { return rect; }
    float getSpeed() const { return speed; }
    float getMass() const { return mass; }
    float getLength() const { return length; }
    float getKp() const { return Kp; }
    float getKi() const { return Ki; }
    float getKd() const { return Kd; }
    int getGoForArm() const { return goForArm; }

    // Setters
    void setOrigin(const Vector2& newOrigin) { origin = newOrigin; }
    void setRotation(float newRotation) { rotation = newRotation; }
    void setColor(const Color& newColor) { color = newColor; }
    void setRect(const Rectangle& newRect) { rect = newRect; }
    void setSpeed(float newSpeed) { speed = newSpeed; }
    void setMass(float newMass) { mass = newMass; }
    void setLength(float newLength) { length = newLength; }
    void setKp(float newKp) { Kp = newKp; }
    void setKi(float newKi) { Ki = newKi; }
    void setKd(float newKd) { Kd = newKd; }
    void setGoForArm(int newGoForArm) { goForArm = newGoForArm; }

    void drawArm() const {
        DrawRectanglePro(rect, origin, rotation, color);
    }
    void controlArm();
    void controlPIDValues();
    void applyGravity();
    void applyPhysics();
    void moveArm(Arm* startArm,Arm* targetArm);

private:
    //Raylib stuff
    float speed;
    //Physics
    float mass;
    float length;
    //Pid
    float Kp;
    float Ki;
    float Kd;
    //Other
    int goForArm;
};