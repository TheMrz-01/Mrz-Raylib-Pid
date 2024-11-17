#pragma once 
#include <string>
#include "raylib.h"

const float gravity = 9.81f;
const float pi = 3.14159f;

class Motor {
public:
    Motor(std::string name,float maxVoltage,float minVoltage,float appliedVoltage,float appliedCurrent,
    float noLoadRpm,float noLoadCurrent,
    float stallTorque,float stallCurrent,float peakPower, 
    float peakEfficiency,float efficiencyAt,float efficiencyAtPower,
    float rotorRadius,float rotorMass) :
    name(name),maxVoltage(maxVoltage),minVoltage(minVoltage),appliedVoltage(appliedVoltage),
    appliedCurrent(appliedCurrent),noLoadRpm(noLoadRpm),noLoadCurrent(noLoadCurrent),
    stallTorque(stallTorque),stallCurrent(stallCurrent),peakPower(peakPower),
    peakEfficiency(peakEfficiency),efficiencyAt(efficiencyAt),
    efficiencyAtPower(efficiencyAtPower),rotorRadius(rotorRadius),rotorMass(rotorMass)
    {}

    //Getters
    std::string getName() const { return name; }
    float getMaxVoltage() const { return maxVoltage; }
    float getMinVoltage() const { return minVoltage; }
    float getAppliedVoltage() const { return appliedVoltage; }
    float getAppliedCurrent() const { return appliedCurrent; }
    float getNoLoadRpm() const { return noLoadRpm; }
    float getNoLoadCurrent() const { return noLoadCurrent; }
    float getStallTorque() const { return stallTorque; }
    float getStallCurrent() const { return stallCurrent; }
    float getPeakPower() const { return peakPower; }
    float getPeakEfficiency() const { return peakEfficiency; }
    float getEfficiencyAt() const { return efficiencyAt; }
    float getEfficiencyAtPower() const { return efficiencyAtPower; }
    float getRotorRadius() const { return rotorRadius; }
    float getRotorMass() const { return rotorMass; }

    // Setters
    void setName(const std::string& name) { this->name = name; }
    void setMaxVoltage(float newMaxVoltage) { maxVoltage = newMaxVoltage; }
    void setMinVoltage(float newMinVoltage) { minVoltage = newMinVoltage; }
    void setAppliedVoltage(float newAppliedVoltage) { appliedVoltage = newAppliedVoltage; }
    void setAppliedCurrent(float newAppliedCurrent) { appliedCurrent = newAppliedCurrent; }
    void setNoLoadRpm(float newNoLoadRpm) { noLoadRpm = newNoLoadRpm; }
    void setNoLoadCurrent(float newNoLoadCurrent) { noLoadCurrent = newNoLoadCurrent; }
    void setStallTorque(float newStallTorque) { stallTorque = newStallTorque; }
    void setStallCurrent(float newStallCurrent) { stallCurrent = newStallCurrent; }
    void setPeakPower(float newPeakPower) { peakPower = newPeakPower; }
    void setPeakEfficiency(float newPeakEfficiency) { peakEfficiency = newPeakEfficiency; }
    void setEfficiencyAt(float newEfficiencyAt) { efficiencyAt = newEfficiencyAt; }
    void setEfficiencyAtPower(float newEfficiencyAtPower) { efficiencyAtPower = newEfficiencyAtPower; }
    void setRotorRadius(float newRotorRadius) { rotorRadius = newRotorRadius; }
    void setRotorMass(float newRotorMass) { rotorMass = newRotorMass; }

    void startMotor();
    void stopMotor();
    void calculateConstants();

private:
    std::string name;
    float maxVoltage;
    float minVoltage;
    float appliedVoltage;
    float appliedCurrent;
    float noLoadRpm;
    float noLoadCurrent;
    float stallTorque; //Nm
    float stallCurrent;
    float peakPower; 
    float peakEfficiency; // %
    float efficiencyAt; //This values coefficient changes
    float efficiencyAtPower; //This values coefficient changes
    float rotorRadius;
    float rotorMass;
};


