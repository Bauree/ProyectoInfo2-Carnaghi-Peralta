#ifndef SENSORMQ2_H
#define SENSORMQ2_H

#include <Arduino.h>

class SensorMQ2 {
public:
    SensorMQ2(int pin);
    void begin();
    int read();

private:
    int _pin;
};

#endif