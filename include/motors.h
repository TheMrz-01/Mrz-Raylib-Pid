#pragma once 
#include <string>
#include "raylib.h"
#include "mrzUtils.h"

class Motor {
public:
    Motor(std::string name,float maxVoltage,float minVoltage,float appliedVoltage,float appliedCurrent,
    float noLoadSpeed,float noLoadCurrent,/*float rOhm, float KvRadPerSecPerVolt,float KtNMPerAmp,*/
    float stallTorque,float stallCurrent,float peakPower, 
    float peakEfficiency,float efficiencyAt,float efficiencyAtPower,
    float rotorRadius,float rotorMass) :
    name(name),maxVoltage(maxVoltage),minVoltage(minVoltage),appliedVoltage(appliedVoltage),
    appliedCurrent(appliedCurrent),noLoadSpeed(noLoadSpeed),noLoadCurrent(noLoadCurrent),
    //rOhm(rOhm),KvRadPerSecPerVolt(KvRadPerSecPerVolt),KtNMPerAmp(KtNMPerAmp),
    stallTorque(stallTorque),stallCurrent(stallCurrent),peakPower(peakPower),
    peakEfficiency(peakEfficiency),efficiencyAt(efficiencyAt),
    efficiencyAtPower(efficiencyAtPower),rotorRadius(rotorRadius),rotorMass(rotorMass)
    {
        this->rOhms = maxVoltage / stallCurrent;
        this->KvRadPerSecPerVolt = noLoadSpeed / (maxVoltage - rOhms * this->noLoadCurrent);
        this->KtNMPerAmp = this->stallTorque / this->stallCurrent;
    }

    //Getters
    std::string getName() const { return name; }
    float getInputVoltage() const { return inputVoltage; }
    float getMaxVoltage() const { return maxVoltage; }
    float getMinVoltage() const { return minVoltage; }
    float getAppliedVoltage() const { return appliedVoltage; }
    float getAppliedCurrent() const { return appliedCurrent; }
    float getNoLoadSpeed() const { return noLoadSpeed; }
    float getNoLoadCurrent() const { return noLoadCurrent; }
    float getROhm() const { return rOhms; }
    float getKvRadPerSecPerVolt() const { return KvRadPerSecPerVolt; }
    float getKtNMPerAmp() const { return KtNMPerAmp; }
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
    void setNoLoadSpeed(float newNoLoadSpeed) { noLoadSpeed = newNoLoadSpeed; }
    void setNoLoadCurrent(float newNoLoadCurrent) { noLoadCurrent = newNoLoadCurrent; }
    void setROhm(float newROhms) { rOhms = newROhms; }
    void setKvRadPerSecPerVolt(float newKvRadPerSecPerVolt) {KvRadPerSecPerVolt = newKvRadPerSecPerVolt; }
    void setKtNMPerAmp(float newKtNMPerAmp) { KtNMPerAmp = newKtNMPerAmp; }
    void setStallTorque(float newStallTorque) { stallTorque = newStallTorque; }
    void setStallCurrent(float newStallCurrent) { stallCurrent = newStallCurrent; }
    void setPeakPower(float newPeakPower) { peakPower = newPeakPower; }
    void setPeakEfficiency(float newPeakEfficiency) { peakEfficiency = newPeakEfficiency; }
    void setEfficiencyAt(float newEfficiencyAt) { efficiencyAt = newEfficiencyAt; }
    void setEfficiencyAtPower(float newEfficiencyAtPower) { efficiencyAtPower = newEfficiencyAtPower; }
    void setRotorRadius(float newRotorRadius) { rotorRadius = newRotorRadius; }
    void setRotorMass(float newRotorMass) { rotorMass = newRotorMass; }

    void setVoltage(float voltageInputs);
    float getSpeed(float torqueNm,float voltageInput);
    float getCurrent(float speedRadiansPerSec,float voltageInput);
    float getVoltage(float torqueNm,float speedRadiansPerSec);
    float getTorque(float currentAmpere);
    void stopMotor();
    void breaker();
    float calculateSpeed();
    float calculateTorque();
    void resetFully();
    void reset();

private:
    std::string name;
    float inputVoltage = 0;
    float maxVoltage = 0;
    float minVoltage = 0;
    float appliedVoltage = 0;
    float appliedCurrent = 0;
    float noLoadSpeed = 0;//Rads/s
    float noLoadCurrent = 0;
    float rOhms = 0;
    float KvRadPerSecPerVolt = 0;
    float speedRadsPerSec = 0;
    float torqueNm = 0;
    float currentAmpere = 0;
    float KtNMPerAmp = 0;
    float stallTorque = 0; //Nms
    float stallCurrent = 0; //Amps
    float peakPower = 0; 
    float peakEfficiency = 0; // %
    float efficiencyAt = 0; //This values coefficient changes
    float efficiencyAtPower = 0; //This values coefficient changes
    float rotorRadius = 0;
    float rotorMass = 0;
    //Calculation Results
    float torque = 0;
    float speed = 0;
    float current = 0;
    float voltage = 0;
};


