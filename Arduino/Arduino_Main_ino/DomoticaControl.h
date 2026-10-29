#ifndef DOMOTICA_CONTROL_H
#define DOMOTICA_CONTROL_H

#include <Arduino.h>

// Definición de Estados para la Máquina de Estados (Requisito de cátedra)
enum EstadoSistema {
  ESTADO_DESARMADO,
  ESTADO_ARMADO,
  ESTADO_ALARMA_DISPARADA
};

class SistemaDomotica {
  private:
    // Pines de Hardware
    uint8_t pinBotonArmar;
    uint8_t pinPIR;
    uint8_t pinBuzzer;
    uint8_t pinLedR;
    uint8_t pinLedG;
    uint8_t pinLedB;
    uint8_t pinesLuminarias[4];

    // Variables de estado interno
    EstadoSistema estadoActual;
    bool estadoAnteriorBotonArmar;
    unsigned long ultimoTiempoEnvio;

  public:
    // Constructor
    SistemaDomotica(uint8_t btnArmar, uint8_t pir, uint8_t buzzer, uint8_t ledR, uint8_t ledG, uint8_t ledB, uint8_t lum1, uint8_t lum2, uint8_t lum3, uint8_t lum4);

    // Métodos principales
    void inicializar();
    void actualizar();
    
    // Control de actuadores desde la PC (Processing)
    void setLuminaria(uint8_t indice, bool encender);
    
    // Consultas y reportes seriales
    EstadoSistema getEstadoActual();
    void enviarReporteSerial();
};

#endif