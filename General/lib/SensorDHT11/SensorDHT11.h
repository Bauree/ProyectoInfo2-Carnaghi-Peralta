#ifndef SENSORDHT11_H 
#define SENSORDHT11_H
//directivas de inclusión.
#include <Arduino.h> 
#include <DHT.h>

class SensorDHT11 { // Declara la clase SensorDHT11 para encapsular la funcionalidad del mismo.
public:
    SensorDHT11(int pin); //Constructor: inicializa sensor en el pin.
    //Métodos:
    void begin(); //Inicializar el sensor.
    float readTemperature(); //Leer y devolver temp.
    float readHumidity();//Hum.

private:
    int _pin; //Pin conexión.
    float _temperature; //Temperatura
    float _humidity; //Humedad.
    DHT dht; //Obj. maneja comunicación sensor.
};

#endif