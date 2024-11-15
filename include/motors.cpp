#include "motors.h"
#include "arms.h"

extern MechArm mechArm;

//Falcon500
std::string fName = "Falcon 500";
float fVoltage = 12.0f;
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
float x60Voltage = 12.0f;
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

Motor Falcon500(fName,fVoltage,fNoLoadRpm,fNoLoadCurrent,fStallTorque,fStallCurrent,
fPeakPower,fPeakEfficiency,fEfficiencyAt,fEfficiencyAtPower,fRotorRadius,fRotorMass);

Motor KrakenX60(x60Name,x60Voltage,x60NoLoadRpm,x60NoLoadCurrent,x60StallTorque,
x60StallCurrent,x60PeakPower,x60PeakEfficiency,x60EfficiencyAt,
x60EfficiencyAtPower,x60RotorRadius,x60RotorMass);

//To start
float Kt; //Kt is torque constant (in Nm/A)
float Ke; //Back EMF constant (in V·s/rad)
float Imotor= 0; //Motor Current
float Wno_load; //Angular velocity at no-load (in radians per second)
float rmotor= 0;//Motor torque
float Wmotor = 0; //The motor's angular velocity (in radians per second)
float amotor= 0;//The motor's angular acceleration (in radians per second squared)
float Jmotor;//Moment of Inertia
float Rmotor = 0.017;//Internal resistance Ohm || [WARNING] THIS IS A ESTIMATION
float Warm;//Arm angular velocity
float Vlinear;//Linear velocity

//To stop
float a_deacceleration = 0;
float rfirction = 0;
float Jarm = 0;

float getKt(Motor* motor){
    Kt = motor->getStallTorque() / motor->getStallCurrent();
    return Kt;
}

float getWno_load(Motor* motor){
    Wno_load = 2*pi * motor->getNoLoadRpm() / 60;
    return Wno_load;
}

float getKe(Motor* motor){
    Ke = motor->getVoltage() / getWno_load(motor);
    return Ke;
}

float getJmotor(Motor* motor){
    Jmotor = 1/2 * motor->getRotorMass() * motor->getRotorRadius();
    return Jmotor;
}

float getrmotor(Motor* motor){
    rmotor = getKt(motor) * Imotor;
    return rmotor;
}

float getamotor(Motor* motor){
    amotor = getrmotor(motor) / (getJmotor(motor) / mechArm.getLength());
    return amotor;
}

float getWmotor(Motor* motor){
    Wmotor = Wmotor + getamotor(motor) * GetFrameTime();
    return Wmotor;
}

float getImotor(Motor* motor){
    Imotor = (motor->getVoltage() - getKe(motor) * getWmotor(motor)) / Rmotor;
    return Imotor;
}

float getWarm(Motor* motor){
    Warm = getWmotor(motor);
    return Warm;
}

float getVlinear(Motor* motor){
    Vlinear = mechArm.getLength() * getWarm(motor);
    return Vlinear;
}

void Motor::startMotor(){
    if(voltage <= 0)
        return;

    this->setVoltage(voltage);
    getKt(this);
    getWno_load(this);
    getKe(this);
    getJmotor(this);
    getrmotor(this);
    getamotor(this);
    getWmotor(this);
    getImotor(this);
    getWarm(this);
    getVlinear(this);

    //Try using Warm instead of Vlinear
    mechArm.setRotation(mechArm.getRotation() + Vlinear * GetFrameTime());

    return;
}

float getrfiction(Motor* motor){
    //Try acjusting the value of damping
    rfirction = -damping * getVlinear(motor);
    return rfirction;
}

float geta_deacceleration(Motor* motor){
    a_deacceleration = -getrfiction(motor)/(Jmotor + Jarm);
    return a_deacceleration;
}

float activateDeacceleration(Motor* motor){
    //Try using Warm
    Vlinear = Vlinear - geta_deacceleration(motor) * GetFrameTime();
    return Vlinear;
}

void Motor::stopMotor(){
    this->setVoltage(0);
    getrfiction(this);
    geta_deacceleration(this);
    activateDeacceleration(this);

    mechArm.setRotation(mechArm.getRotation() - Vlinear * GetFrameTime());

    return;
}