#ifndef DOMOTICA_MANAGER_H
#define DOMOTICA_MANAGER_H

#include <Arduino.h>
#include <ESP32Servo.h>
#include <LittleFS.h>

class DomoticaManager {
private:
    uint8_t pinPIR;
    uint8_t pinLED;
    uint8_t pinServo;
    Servo servoPuerta;
    
    bool estadoLuzActual;

public:
    // Constructor
    DomoticaManager(uint8_t pir, uint8_t led, uint8_t servo);

    // Métodos de inicialización y hardware
    void begin();
    bool verificarMovimiento();
    void setLuz(bool encender);
    void accionarPuerta(int grados);
    
    // Método para persistencia en archivos (Modo Append)
    void guardarLog(String mensaje);
};

#endif
