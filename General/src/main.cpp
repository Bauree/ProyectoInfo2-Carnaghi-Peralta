#include <Arduino.h>
#include "SensorDHT11.h"
#include "SensorMQ2.h"

#define DHTPIN 13
#define MQ2PIN 34

SensorDHT11 sensorDHT11(DHTPIN);
SensorMQ2 sensorMQ2(MQ2PIN);

void setup() {
    Serial.begin(115200);
    sensorDHT11.begin();
    sensorMQ2.begin();
}

void loop() {
    float temperatura = sensorDHT11.readTemperature();
    float humedad = sensorDHT11.readHumidity();
    int NivelHumo = sensorMQ2.read();

    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" *C");

    Serial.print("Humedad: ");
    Serial.print(humedad);
    Serial.println(" %");

    Serial.print("Nivel de Humo: ");
    Serial.println(NivelHumo);

    delay(2000);
}
