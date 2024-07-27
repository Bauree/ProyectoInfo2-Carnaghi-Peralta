#ifndef SENSORDHT11_H
#define SENSORDHT11_H

#include <Arduino.h>
#include <DHT.h>

class SensorDHT11 {
public:
    SensorDHT11(int pin);
    void begin();
    float readTemperature();
    float readHumidity();

private:
    int _pin;
    float _temperature;
    float _humidity;
    DHT dht;
};

#endif
