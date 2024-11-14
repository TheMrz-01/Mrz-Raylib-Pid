#pragma once 

typedef struct Motor {
    void (*start)();
    void (*stop)();
    float voltage;
    const float NoLoadRpm;
    const float StallCurrent;
    const float NoLoadTorque;
    const float NoLoadCurrent;
    const float maxPower;
} Motor;

typedef struct CIM {
    Motor motor;
} CIM;

typedef struct Falcon500 {
    Motor motor;
} Falcon500;

typedef struct KrakenX44 {
    Motor motor;
} KrakenX44;