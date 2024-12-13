#include "SensorDHT11.h"

#define DHTTYPE DHT11

SensorDHT11::SensorDHT11(int pin) : _pin(pin), _temperature(0), _humidity(0), dht(pin, DHTTYPE) {}

void SensorDHT11::begin() {
    dht.begin();
}

float SensorDHT11::readTemperature() {
    _temperature = dht.readTemperature();
    return _temperature;
}

float SensorDHT11::readHumidity() {
    _humidity = dht.readHumidity();
    return _humidity;
}
