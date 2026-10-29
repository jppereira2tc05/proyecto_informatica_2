#include "DomoticaManager.h"

// Definición de Pines
const int PIN_PIR = 13;
const int PIN_LED = 2;   // LED incorporado o externo de prueba
const int PIN_SERVO = 18;

// Instancia de nuestra clase propia
DomoticaManager casa(PIN_PIR, PIN_LED, PIN_SERVO);

// Enumeración de Estados para la FSM
typedef enum {
    ESTADO_INIT,
    ESTADO_IDLE,
    ESTADO_DETECTAR_MOVIMIENTO,
    ESTADO_PROCESAR_COMANDO
} EstadoSistema_t;

EstadoSistema_t estadoActual = ESTADO_INIT;
String comandoSerial = "";

void setup() {
    Serial.begin(115200);
    delay(1000);
    estadoActual = ESTADO_INIT;
}

void loop() {
    switch (estadoActual) {
        case ESTADO_INIT:
            casa.begin();
            Serial.println("[OK] Sistema Domotico Iniciado");
            estadoActual = ESTADO_IDLE;
            break;

        case ESTADO_IDLE:
            // 1. Revisar si hay eventos locales (Sensor PIR)[cite: 4]
            if (casa.verificarMovimiento()) {
                estadoActual = ESTADO_DETECTAR_MOVIMIENTO;
                break;
            }

            // 2. Revisar si llegan comandos desde Processing por el puerto serie
            if (Serial.available() > 0) {
                comandoSerial = Serial.readStringUntil('\n');
                comandoSerial.trim(); // Limpiar espacios o saltos de línea
                estadoActual = ESTADO_PROCESAR_COMANDO;
                break;
            }
            break;

        case ESTADO_DETECTAR_MOVIMIENTO:
            Serial.println("EVENTO:MOV_DETECTADO");
            casa.guardarLog("MOVIMIENTO_DETECTADO_PIR");
            delay(1000); // Anti-rebote simple para el sensor PIR
            estadoActual = ESTADO_IDLE;
            break;

        case ESTADO_PROCESAR_COMANDO:
            // Procesamiento de comandos entrantes desde Processing[cite: 2, 4]
            if (comandoSerial == "CMD:LUZ_ON") {
                casa.setLuz(true);
                Serial.println("RESPUESTA:LUZ_OK_ON");
            } 
            else if (comandoSerial == "CMD:LUZ_OFF") {
                casa.setLuz(false);
                Serial.println("RESPUESTA:LUZ_OK_OFF");
            } 
            else if (comandoSerial.startsWith("CMD:PUERTA:")) {
                int grados = comandoSerial.substring(11).toInt();
                casa.accionarPuerta(grados);
                Serial.println("RESPUESTA:PUERTA_OK");
            }
            
            comandoSerial = "";
            estadoActual = ESTADO_IDLE;
            break;
    }
}
