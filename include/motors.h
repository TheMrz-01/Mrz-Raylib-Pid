#pragma once 

class Motor {
    void (*start)();
    void (*stop)();
    float voltage;
    const float NoLoadRpm;
    const float StallCurrent;
    const float NoLoadTorque;
    const float NoLoadCurrent;
    const float maxPower;
};
