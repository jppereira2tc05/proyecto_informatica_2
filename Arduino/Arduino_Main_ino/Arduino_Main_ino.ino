#include "DomoticaControl.h"

// Instanciación del objeto del sistema domótico mapeando los pines:
// Parámetros: (Pin Botón Armar, Pin PIR, Pin Buzzer, Pin LED_R, Pin LED_G, Pin LED_B, Lum1, Lum2, Lum3, Lum4)
SistemaDomotica casa(2, 3, 4, 5, 6, 7, 8, 9, 10, 11);

void setup() {
  // Inicializamos comunicación serial a 115200 baudios (tal como lo probamos)
  Serial.begin(115200);
  
  // Inicializamos los pines y estados del sistema
  casa.inicializar();
}

void loop() {
  // 1. Ejecutamos la actualización continua de la máquina de estados y sensores
  casa.actualizar();

  // 2. Procesamiento de comandos entrantes desde Processing vía Puerto Serie
  if (Serial.available() > 0) {
    char comando = Serial.read();

    // Protocolo simple de comandos para las 4 luminarias:
    // '1' a '4' encienden las luminarias respectivamente.
    // 'q', 'w', 'e', 'r' apagan las luminarias 1, 2, 3 y 4 respectivamente.
    switch (comando) {
      case '1': casa.setLuminaria(0, true);  break;
      case 'q': casa.setLuminaria(0, false); break;
      
      case '2': casa.setLuminaria(1, true);  break;
      case 'w': casa.setLuminaria(1, false); break;
      
      case '3': casa.setLuminaria(2, true);  break;
      case 'e': casa.setLuminaria(2, false); break;
      
      case '4': casa.setLuminaria(3, true);  break;
      case 'r': casa.setLuminaria(3, false); break;
    }
  }
}