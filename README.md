# Trabajo Final - Informática II (UTN FRM)
**Proyecto:** Sistema Domótico Inteligente con Arduino y Processing (MVP)

---

## 1. Introducción y Objetivos
El objetivo principal de este trabajo integrador es aplicar y consolidar los conocimientos adquiridos a lo largo de la cursada de **Informática II**, integrando hardware (Arduino Nano) y software de escritorio (Processing) mediante comunicación serial bidireccional. 

El sistema representa un entorno domótico modular, aplicando buenas prácticas de programación, separación de responsabilidades en múltiples archivos y persistencia de datos orientada a la evaluación académica.

---

## 2. Requisitos Mínimos de Aprobación
El desarrollo cumple estrictamente con los lineamientos exigidos por la cátedra para la nota base:
* **Buenas Prácticas de Programación:** Código modular y comentado.
* **Comunicación Bidireccional:** Enlace serie entre Arduino y PC a 115200 baudios.
* **Interfaz Gráfica en PC:** Desarrollada en Processing con paneles de control visuales.
* **Lectura y Accionamiento:** Control digital de actuadores y monitoreo de sensores físicos.
* **Señalización Local:** Indicación de estados principales mediante LEDs de estado en Arduino.
* **Máquina de Estados:** Implementada tanto en el firmware como en el software de interfaz.
* **Clases y Modularidad:** Creación y uso de clases personalizadas (`InterfacePanel`, `EventLogger`, etc.), separando la declaración de tipos de la lógica.
* **Persistencia de Datos:** Registro de eventos en modo *append* dentro del directorio `/data`, permitiendo recuperar historiales sin sobrescribir registros previos.
* **Control de Versiones:** Repositorio estructurado y alojado en GitHub.

---

## 3. Temas Propuestos por la Cátedra
El programa contempla los siguientes ejes temáticos para el desarrollo del trabajo final:
1. **Juegos:** Interfaz en Processing controlada por pulsadores físicos en Arduino.
2. **Sensado Ambiental:** Monitoreo de temperatura y humedad con alarmas por umbrales y guardado de archivos.
3. **Control de Acceso:** Lector de tarjetas/llaveros con habilitación desde Processing y notificación de accesos.
4. **Domótica:** Conexión de LEDs y sensores de movimiento (opcionalmente con maqueta), control de luces desde Processing y registro de eventos. *(Tema Seleccionado)*
5. **Semáforos Inteligentes:** Control de intersección y simulación de onda verde según tráfico.
6. **ECG (Electrocardiograma):** Simulación y lectura de pulsos cardíacos con almacenamiento y graficación.
7. **Control de Tanques:** Monitoreo de niveles y válvulas de seguridad.
8. **Minipiano:** Instrumento interactivo con buzzer y reproducción/grabación de melodías en archivos.
9. **Joystick para Drone:** Dispositivo físico en Arduino para manipular un simulador.

---

## 4. Tema Elegido: Tema 4 - Domótica
Para este proyecto se optó por el **Tema 4 (Domótica)**, enfocado en el desarrollo de un Producto Mínimo Viable (MVP) robusto y una maqueta física a escala:

* **Arquitectura de Software:**
  * **Arduino:** Control de máquina de estados (Armado, Desarmado, Alarma Disparada), lectura de sensor PIR de presencia, botón único de control y gestión de 4 zonas de iluminación mediante LEDs individuales y un LED RGB indicador de estado general.
  * **Processing:** Interfaz gráfica modular dividida en solapas (`Main`, `InterfacePanel`, `EventLogger`), permitiendo el accionamiento remoto de las luminarias, visualización de alertas en tiempo real y persistencia automática de eventos en archivos de texto.
* **Hardware y Maqueta:**
  * Implementación física sobre placa universal con conector tipo HAT y borneras para asegurar una conexión limpia y profesional.
  * Maqueta física minimalista de vista lateral (corte arquitectónico de dos plantas: 4 habitaciones distribuidas en planta alta y baja) iluminada cenitalmente por las luminarias del sistema.

---

## 5. Estructura del Repositorio
```text
/
├── Arduino/
│   └── Domotica_Nano/          # Código fuente del firmware modular
├── Processing/
│   └── Domotica_PC/            # Sketch principal y solapas (InterfacePanel, EventLogger)
│       └── data/               # Archivos de registro histórico (log.txt)
└── README.md                   # Documentación oficial del proyecto
```

---
*Desarrollado para la materia Informática II - UTN Facultad Regional Mendoza.*