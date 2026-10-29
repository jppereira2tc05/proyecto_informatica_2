#include "DomoticaControl.h"

// Constructor: Asigna pines y configura variables iniciales
SistemaDomotica::SistemaDomotica(uint8_t btnArmar, uint8_t pir, uint8_t buzzer, uint8_t ledR, uint8_t ledG, uint8_t ledB, uint8_t lum1, uint8_t lum2, uint8_t lum3, uint8_t lum4) {
  pinBotonArmar = btnArmar;
  pinPIR = pir;
  pinBuzzer = buzzer;
  pinLedR = ledR;
  pinLedG = ledG;
  pinLedB = ledB;
  
  pinesLuminarias[0] = lum1;
  pinesLuminarias[1] = lum2;
  pinesLuminarias[2] = lum3;
  pinesLuminarias[3] = lum4;

  estadoActual = ESTADO_DESARMADO;
  estadoAnteriorBotonArmar = HIGH;
  ultimoTiempoEnvio = 0;
}

// Inicialización de pines (equivalente al setup)
void SistemaDomotica::inicializar() {
  pinMode(pinBotonArmar, INPUT_PULLUP);
  pinMode(pinPIR, INPUT);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinLedR, OUTPUT);
  pinMode(pinLedG, OUTPUT);
  pinMode(pinLedB, OUTPUT);

  for (uint8_t i = 0; i < 4; i++) {
    pinMode(pinesLuminarias[i], OUTPUT);
    digitalWrite(pinesLuminarias[i], LOW);
  }

  // Estado inicial: Todo apagado / sistema desarmado (LED Verde)
  digitalWrite(pinLedR, LOW);
  digitalWrite(pinLedG, HIGH);
  digitalWrite(pinLedB, LOW);
  digitalWrite(pinBuzzer, LOW);
}

// Actualización lógica continua (máquina de estados)
void SistemaDomotica::actualizar() {
  // 1. Lectura del botón de alarma (con anti-rebote simple por flanco)
  bool lecturaBoton = digitalRead(pinBotonArmar);
  if (lecturaBoton == LOW && estadoAnteriorBotonArmar == HIGH) {
    // Cambio de estado seguro entre DESARMADO y ARMADO
    if (estadoActual == ESTADO_DESARMADO) {
      estadoActual = ESTADO_ARMADO;
      // LED Azul: Sistema Armado
      digitalWrite(pinLedR, LOW);
      digitalWrite(pinLedG, LOW);
      digitalWrite(pinLedB, HIGH);
    } else if (estadoActual == ESTADO_ARMADO || estadoActual == ESTADO_ALARMA_DISPARADA) {
      estadoActual = ESTADO_DESARMADO;
      // LED Verde: Sistema Desarmado
      digitalWrite(pinLedR, LOW);
      digitalWrite(pinLedG, HIGH);
      digitalWrite(pinLedB, LOW);
      digitalWrite(pinBuzzer, LOW);
    }
    delay(200); // Pequeño debounce por software
  }
  estadoAnteriorBotonArmar = lecturaBoton;

  // 2. Lógica según el estado actual de la máquina de estados
  switch (estadoActual) {
    case ESTADO_DESARMADO:
      // Sin monitoreo de intrusión activo
      break;

    case ESTADO_ARMADO:
      // Monitoreando el sensor PIR
      if (digitalRead(pinPIR) == HIGH) {
        estadoActual = ESTADO_ALARMA_DISPARADA;
        // LED Rojo intermitente / encendido y Buzzer activo
        digitalWrite(pinLedR, HIGH);
        digitalWrite(pinLedG, LOW);
        digitalWrite(pinLedB, LOW);
      }
      break;

    case ESTADO_ALARMA_DISPARADA:
      // Suena la chicharra de forma intermitente
      digitalWrite(pinBuzzer, (millis() / 500) % 2 == HIGH ? HIGH : LOW);
      break;
  }

  // 3. Envío periódico de telemetría a Processing (cada 500ms)
  if (millis() - ultimoTiempoEnvio > 500) {
    enviarReporteSerial();
    ultimoTiempoEnvio = millis();
  }
}

// Control individual de luminarias desde Processing
void SistemaDomotica::setLuminaria(uint8_t indice, bool encender) {
  if (indice < 4) {
    digitalWrite(pinesLuminarias[indice], encender ? HIGH : LOW);
  }
}

// Devuelve el estado actual para la lógica
EstadoSistema SistemaDomotica::getEstadoActual() {
  return estadoActual;
}

// Reporte empaquetado por puerto serie hacia Processing
void SistemaDomotica::enviarReporteSerial() {
  // Formato simple: ESTADO_ALARMA, ESTADO_PIR, ESTADO_LUM1, LUM2, LUM3, LUM4
  Serial.print("ALM:");
  Serial.print(estadoActual);
  Serial.print(",PIR:");
  Serial.print(digitalRead(pinPIR));
  Serial.print(",L1:");
  Serial.print(digitalRead(pinesLuminarias[0]));
  Serial.print(",L2:");
  Serial.print(digitalRead(pinesLuminarias[1]));
  Serial.print(",L3:");
  Serial.print(digitalRead(pinesLuminarias[2]));
  Serial.print(",L4:");
  Serial.println(digitalRead(pinesLuminarias[3]));
}