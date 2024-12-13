#include <Arduino.h>
#include "SensorDHT11.h"

#define DHTPIN 13

SensorDHT11 sensor(DHTPIN);

void setup() {
    Serial.begin(115200);
    sensor.begin();
}

void loop() {
    float temperatura = sensor.readTemperature();
    float humedad = sensor.readHumidity();

    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" *C");

    Serial.print("Humedad: ");
    Serial.print(humedad);
    Serial.println(" %");

    delay(2000);
}
