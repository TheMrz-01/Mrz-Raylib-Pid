#include "motors.h"
#include "arms.h"

extern MechArm mechArm;

//Falcon500
std::string fName = "Falcon 500";
float fMaxVoltage = 12.0f;
float fMinVoltage = 0.0f;
float fAppliedVoltage = 0.0f;
float fAppliedCurrent = 0.0f;
float fNoLoadRpm = 6380.0f;
float fNoLoadCurrent = 1.5f;
float fStallTorque = 4.69f;
float fStallCurrent = 257.0f;
float fPeakPower = 783.0f;
float fPeakEfficiency = 87.0f;//
float fEfficiencyAt = 83.0f;//40A / 12V
float fEfficiencyAtPower = 400.0f;//Watt
float fRotorRadius = 4.826f;//Cm [WARINING] THIS IS AN ESTIMATION || ORIGINAL IS 2.2
float fRotorMass = 0.453592f;//kgs [WARINING] THIS IS AN ESTIMATION|| ORIGINAL IS 1.25

//KrakenX60
std::string x60Name = "Kraken X60";
float x60MaxVoltage = 12.0f;
float x60MinVoltage = 0.0f;
float x60AppliedVoltage = 0.0f;
float x60AppliedCurrent = 0.0f;
float x60NoLoadRpm = 6000.0f;
float x60NoLoadCurrent = 2.0f;
float x60StallTorque = 7.09f;
float x60StallCurrent = 366.0f;
float x60PeakPower = 1.0108f;
float x60PeakEfficiency = 87.0f;
float x60EfficiencyAt = 87.0f;//30A / 12V
float x60EfficiencyAtPower = 313.0f;//Watt
float x60RotorRadius = 4.572f; //Cm [WARINING] THIS IS AN ESTIMATION || ORIGINAL IS 2.0
float x60RotorMass = 0.408233f;//Kgs [WARINING] THIS IS AN ESTIMATION || ORIGINAL IS 1.2

Motor Falcon500(fName,fMaxVoltage,fMinVoltage,fAppliedVoltage,x60AppliedCurrent,fNoLoadRpm,fNoLoadCurrent,fStallTorque,fStallCurrent,
fPeakPower,fPeakEfficiency,fEfficiencyAt,fEfficiencyAtPower,fRotorRadius,fRotorMass);

Motor KrakenX60(x60Name,x60MaxVoltage,x60MinVoltage,x60AppliedVoltage,fAppliedCurrent,x60NoLoadRpm,x60NoLoadCurrent,x60StallTorque,
x60StallCurrent,x60PeakPower,x60PeakEfficiency,x60EfficiencyAt,
x60EfficiencyAtPower,x60RotorRadius,x60RotorMass);


void Motor::startMotor(){
    

    return;
}

void Motor::stopMotor(){

    return;
}