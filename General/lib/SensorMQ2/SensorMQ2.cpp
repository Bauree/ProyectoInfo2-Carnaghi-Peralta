#include "SensorMQ2.h" //Incluimos archivo de cabecera

SensorMQ2::SensorMQ2(int pin) : _pin(pin) {} //Contructor de la clase. Inicializa el obj. y almacena N. de pin

void SensorMQ2::begin() {
    pinMode(_pin, INPUT); //Setea entrada digittal al sensor
}

int SensorMQ2::read() {
    return analogRead(_pin); //lee valor analog del pin y lo devuelve.
}