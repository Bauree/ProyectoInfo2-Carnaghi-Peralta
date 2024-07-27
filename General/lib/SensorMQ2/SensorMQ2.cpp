#include "SensorMQ2.h"

SensorMQ2::SensorMQ2(int pin) : _pin(pin) {}

void SensorMQ2::begin() {
    pinMode(_pin, INPUT);
}

int SensorMQ2::read() {
    return analogRead(_pin);
}
