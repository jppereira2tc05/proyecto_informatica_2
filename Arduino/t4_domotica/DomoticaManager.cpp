#include "DomoticaManager.h"

DomoticaManager::DomoticaManager(uint8_t pir, uint8_t led, uint8_t servo) {
    pinPIR = pir;
    pinLED = led;
    pinServo = servo;
    estadoLuzActual = false;
}

void DomoticaManager::begin() {
    pinMode(pinPIR, INPUT);
    pinMode(pinLED, OUTPUT);
    digitalWrite(pinLED, LOW);

    // Inicializar Servo en ESP32 (la librería maneja los timers automáticamente)
    servoPuerta.setPeriodHertz(50);
    servoPuerta.attach(pinServo, 500, 2400);
    servoPuerta.write(0); // Posición inicial cerrada

    // Inicializar Sistema de Archivos LittleFS para los registros
    if (!LittleFS.begin(true)) {
        Serial.println("[!] Error al montar LittleFS");
    } else {
        Serial.println("[OK] LittleFS montado correctamente");
    }
}

bool DomoticaManager::verificarMovimiento() {
    return digitalRead(pinPIR) == HIGH;
}

void DomoticaManager::setLuz(bool encender) {
    estadoLuzActual = encender;
    digitalWrite(pinLED, estadoLuzActual ? HIGH : LOW);
    
    // Registrar el cambio de estado en archivo
    String estadoStr = estadoLuzActual ? "LUZ_ENCENDIDA" : "LUZ_APAGADA";
    guardarLog(estadoStr);
}

void DomoticaManager::accionarPuerta(int grados) {
    servoPuerta.write(grados);
    guardarLog("PUERTA_MOVIDA_A_" + String(grados) + "_GRADOS");
}

void DomoticaManager::guardarLog(String mensaje) {
    // Abrir archivo en modo APPEND ("a") para no borrar lo anterior[cite: 1, 4]
    File archivo = LittleFS.open("/eventos_domotica.txt", FILE_APPEND);
    if (!archivo) {
        Serial.println("[!] Error al abrir el archivo de log para escritura");
        return;
    }
    
    archivo.println(mensaje);
    archivo.close();
}
