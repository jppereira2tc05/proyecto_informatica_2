import processing.serial.*;

Serial puertoSerial;
InterfacePanel panelControl;
EventLogger logger;

// Arreglos para almacenar los estados actuales que llegan de Arduino
int estadoAlarma = 0; // 0: Desarmado, 1: Armado, 2: Disparado
int estadoPir = 0;    // 0: Normal, 1: Movimiento
boolean[] estadosLuminarias = {false, false, false, false};

void setup() {
  size(600, 460); // <-- El tamaño total de la ventana va aquí una sola vez
  frameRate(30);
  
  // Muestra los puertos disponibles en la consola abajo
  printArray(Serial.list()); 
  String puertoNombre = Serial.list()[1]; // O ajusta el índice si usas otro puerto
  puertoSerial = new Serial(this, puertoNombre, 115200);
  puertoSerial.bufferUntil('\n'); // Espera al salto de línea para leer el paquete completo
  
  // Inicializamos el registrador de eventos (crea el archivo en modo append)
  logger = new EventLogger("historial_domotica.txt");
  
  // Instanciamos nuestro panel de control visual
  panelControl = new InterfacePanel(25, 25, 550, 300);
}

void draw() {
  background(30);
  
  // Dibujamos el panel superior pasándole los estados actuales
  panelControl.dibujar(estadoAlarma, estadoPir, estadosLuminarias);
  
  // Dibujamos el historial de eventos en la parte inferior
  logger.dibujarHistorial(25, 335, 550, 110);
}

// Evento que se ejecuta cada vez que llega una línea completa por el puerto serie desde Arduino
void serialEvent(Serial p) {
  String mensaje = p.readStringUntil('\n');
  if (mensaje != null) {
    mensaje = trim(mensaje);
    
    // El formato que envía Arduino es: ALM:x,PIR:x,L1:x,L2:x,L3:x,L4:x
    try {
      String[] partes = split(mensaje, ',');
      if (partes.length >= 6) {
        int nuevoAlarma = int(split(partes[0], ':')[1]);
        int nuevoPir = int(split(partes[1], ':')[1]);
        
        // Registramos en el logger si cambia el estado de la alarma
        if (nuevoAlarma != estadoAlarma) {
          if (nuevoAlarma == 1) logger.registrarEvento("Alarma Armada físicamente");
          else if (nuevoAlarma == 0) logger.registrarEvento("Alarma Desarmada");
          else if (nuevoAlarma == 2) logger.registrarEvento("¡ALARMA DISPARADA (Intrusión)!");
        }
        
        // Registramos si el PIR detecta movimiento por primera vez
        if (nuevoPir == 1 && estadoPir == 0) {
          logger.registrarEvento("Sensor PIR: Movimiento detectado");
        }
        
        estadoAlarma = nuevoAlarma;
        estadoPir = nuevoPir;
        
        estadosLuminarias[0] = int(split(partes[2], ':')[1]) == 1;
        estadosLuminarias[1] = int(split(partes[3], ':')[1]) == 1;
        estadosLuminarias[2] = int(split(partes[4], ':')[1]) == 1;
        estadosLuminarias[3] = int(split(partes[5], ':')[1]) == 1;
      }
    } catch (Exception e) {
      // Ignoramos errores de parsing sueltos
    }
  }
}

// Manejo de clics del mouse para interactuar con las luces
void mousePressed() {
  int indiceLuz = panelControl.verificarClick(mouseX, mouseY);
  
  if (indiceLuz != -1) {
    estadosLuminarias[indiceLuz] = !estadosLuminarias[indiceLuz];
    
    // Registramos la acción del usuario en el archivo y en memoria
    String nombreLuz = "Luz " + (indiceLuz + 1);
    String estadoAccion = estadosLuminarias[indiceLuz] ? "Encendida desde consola" : "Apagada desde consola";
    logger.registrarEvento(nombreLuz + " - " + estadoAccion);
    
    // Protocolo de comandos hacia el Arduino Nano:
    if (indiceLuz == 0) {
      puertoSerial.write(estadosLuminarias[0] ? '1' : 'q');
    } else if (indiceLuz == 1) {
      puertoSerial.write(estadosLuminarias[1] ? '2' : 'w');
    } else if (indiceLuz == 2) {
      puertoSerial.write(estadosLuminarias[2] ? '3' : 'e');
    } else if (indiceLuz == 3) {
      puertoSerial.write(estadosLuminarias[3] ? '4' : 'r');
    }
  }
}
