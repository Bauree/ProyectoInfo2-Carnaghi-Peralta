#ifndef SENSORMQ2_H
#define SENSORMQ2_H
//Directivas de inclusión 
#include <Arduino.h> //para el analog y pinmode

class SensorMQ2 {
public:
    SensorMQ2(int pin); //Constructor que inicializa pin
    //Métodos:
    void begin(); //Configura pin input
    int read(); //Leer datos del sensor.

private:
    int _pin; //Pin sensor
};

#endif