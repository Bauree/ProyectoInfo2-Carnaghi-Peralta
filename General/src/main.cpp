#include <Arduino.h>
#include "SensorDHT11.h"
#include "SensorMQ2.h"
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>  
#include <SD.h>

//Pines:
#define DHTPIN 32
#define MQ2PIN 34
#define L_PIN 14
#define T_PIN 27
#define SD_CS 5

//Obejetos para manejar:
SensorDHT11 sensorDHT11(DHTPIN); 
SensorMQ2 sensorMQ2(MQ2PIN);

// AsyncWebServer inicialización del servidor.
AsyncWebServer server(80); //Server HTTP port 80.

unsigned long lastSaveTime = 0; // Marca de tiempo para el guardado

void notFound(AsyncWebServerRequest *request) { //método para intentar acceder a una ruta que no está definida.
  request->send(404, "text/plain", "Not found"); //Responde con codigo y mensaje.
}

void setup() {
    Serial.begin(115200); //Inicializa la comunicación serial (en bps).

    // Inicializa SPIFFS. Monta el sist. de archhivos. Si falla, hay mensaje.
    if (!SPIFFS.begin(true)) {
        Serial.println("Error al montar SPIFFS");
        return;
    }

        if (!SD.begin(SD_CS)) { //inicialización de la tarjeta SD
        Serial.println("Error al inicializar la tarjeta SD");
    } else {
        Serial.println("Tarjeta SD inicializada correctamente");
    }

    WiFi.softAP("ESP32-AP", "12345678");// Config. WiFi access point.
    Serial.println("AP Iniciado");
    IPAddress IP = WiFi.softAPIP(); //IP del AP.

    //Configuración sensores: (llamada de métodos)
    sensorDHT11.begin();
    sensorMQ2.begin();

    pinMode(L_PIN, OUTPUT);
    pinMode(T_PIN, OUTPUT);

    //Los recursos web almacenados en el sistema de archivos:
    // SPIFFS página principal 
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/index.html", "text/html"); //Sirve el archivo HTML.
    });

    // SPIFFS style CSS
    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/style.css", "text/css"); //Lo mismo para e CSS.
    });

    // send data sens. -> JSON. llama a los métodos.
    server.on("/data", HTTP_GET, [](AsyncWebServerRequest *request){
        //Lectores:
        float temperatura = sensorDHT11.readTemperature();
        float humedad = sensorDHT11.readHumidity();
        int nivelHumo = sensorMQ2.read();
        int luz = digitalRead(L_PIN);
        int traba = digitalRead(T_PIN);

        //Crea un objeto de tipo JSON con los datos recopilados.
        String jsonData = 
                        "{\"temperatura\": " + String(temperatura) + 
                        ", \"humedad\": " + String(humedad) + 
                        ", \"humo\": " + String(nivelHumo) + 
                        ", \"lampara\": " + String(luz) + 
                        ", \"traba\": " + String(traba) + "}";
        
        request->send(200, "application/json", jsonData); //Envía datos.
    });

    // Control de Lámpara y Traba. Maneja solicitudes HTTP.
    server.on("/LAMPARA=ON", HTTP_GET, [](AsyncWebServerRequest *request){
        digitalWrite(L_PIN, HIGH); //Enciende la lámpara.
        request->send(200, "text/plain", "Lámpara Encendida");
    });

    server.on("/LAMPARA=OFF", HTTP_GET, [](AsyncWebServerRequest *request){
        digitalWrite(L_PIN, LOW); //La apaga.
        request->send(200, "text/plain", "Lámpara Apagada");
    });

    server.on("/TRABA=ON", HTTP_GET, [](AsyncWebServerRequest *request){
        digitalWrite(T_PIN, HIGH); //Activa la traba.
        request->send(200, "text/plain", "Traba Activada");
    });

    server.on("/TRABA=OFF", HTTP_GET, [](AsyncWebServerRequest *request){
        digitalWrite(T_PIN, LOW);//Desactiva.
        request->send(200, "text/plain", "Traba Desactivada");
    });

    server.onNotFound(notFound); //Define manejador para rutas no encontradas.

    // Server Begin
    server.begin();
    Serial.println("Servidor iniciado");
    Serial.println(IP); //Muestra la IP del ESP32
}

void saveDataToSD() {
    // Lee los datos de los sensores
    float temperatura = sensorDHT11.readTemperature();
    float humedad = sensorDHT11.readHumidity();
    int nivelHumo = sensorMQ2.read();
    int luz = digitalRead(L_PIN);
    int traba = digitalRead(T_PIN);

    // Prepara la línea de datos
    String dataLine = "Temperatura: " + String(temperatura) + " °C, " +
                      "Humedad: " + String(humedad) + " %, " +
                      "Humo: " + String(nivelHumo) + ", " +
                      "Lámpara: " + (luz ? "Encendida" : "Apagada") + ", " +
                      "Traba: " + (traba ? "Activada" : "Desactivada") + "\n";

    // Escribe en la SD
    File file = SD.open("/data.txt", FILE_APPEND);
    if (file) {
        file.print(dataLine);
        file.close();
        Serial.println("Datos guardados: " + dataLine);
    } else {
        Serial.println("Error al abrir el archivo en la SD");
    }
}

void loop() {
        // Verifica si ha pasado un minuto (60000 ms)
    if (millis() - lastSaveTime >= 60000) {
        lastSaveTime = millis();
        saveDataToSD(); // Llama a la función de guardado
    }
}