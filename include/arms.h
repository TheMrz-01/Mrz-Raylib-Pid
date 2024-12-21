#pragma once
#include "raylib.h"
#include "mrzUtils.h"
#include <iostream>
#include <cmath>

const float damping = 0.99f;

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
        float mass, float length, float angularAcceleration, float angularVelocity,int goForArm)
        : Arm(rect, origin, rotation, color), speed(speed), angularAcceleration(angularAcceleration)
        ,angularVelocity(angularVelocity), mass(mass), length(length), goForArm(goForArm){}

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
    float getAngularAcceleration() const { return angularAcceleration; }
    float getAngularVelocity() const { return angularVelocity; }

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
    void setAngularAcceleration(float newAngularAcceleration) { angularAcceleration = newAngularAcceleration; }
    void setAngularVelocity(float newAngularVelocity) { angularVelocity = newAngularVelocity; }
    
    //Nuh uh.I'm gonna do IT!
    void setGoForArm(int newGoForArm) { goForArm = newGoForArm; }

    void drawArm() const {
        DrawRectanglePro(rect, origin, rotation, color);
    }
    void controlArm();
    void applyGravity();
    void applyPhysics();
    void reset();

private:
    //Raylib stuff
    float speed;
    //Physics
    float mass;
    float length;
    float angularAcceleration;
    float angularVelocity;
    //Other
    int goForArm;
};