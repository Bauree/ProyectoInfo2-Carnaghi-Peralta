#include "SensorDHT11.h" // Esto incluye el archivo de cabecera donde se define la clase SensorDHT11.

#define DHTTYPE DHT11 //definimos que modelo de DHT estamos usando.         

SensorDHT11::SensorDHT11(int pin) : _pin(pin), _temperature(0), _humidity(0), dht(pin, DHTTYPE) {} //El famoso constructor, inicializa el pin y declara variables internas.

void SensorDHT11::begin() { //inicializa el DHT llamando al método "begin()" del objeto DHT.
    dht.begin();
    
}

float SensorDHT11::readTemperature() {
    _temperature = dht.readTemperature(); //lee temperatura y la guarda en _temperature.
    return _temperature; //devuelve claramente la temperatura.  
}

//lo mismo se hace para humedad.
float SensorDHT11::readHumidity() {
    _humidity = dht.readHumidity(); 
    return _humidity;
}