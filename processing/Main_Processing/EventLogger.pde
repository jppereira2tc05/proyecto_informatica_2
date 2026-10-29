import java.util.ArrayList;

class EventLogger {
  String nombreArchivo;
  ArrayList<String> historialMemoria;
  int maxEventosEnMemoria = 10; // Contenedor en memoria (requisito de cátedra)
  
  EventLogger(String archivo) {
    nombreArchivo = archivo;
    historialMemoria = new ArrayList<String>();
  }
  
  // Registra un evento: lo guarda en memoria y lo escribe en el archivo (Modo Append)
  void registrarEvento(String descripcion) {
    String timestamp = hour() + ":" + minute() + ":" + second() + " - " + descripcion;
    
    // 1. Manejo en memoria (Contenedor tipo ArrayList)
    historialMemoria.add(0, timestamp); // Agrega al principio para ver los más recientes
    if (historialMemoria.size() > maxEventosEnMemoria) {
      historialMemoria.remove(historialMemoria.size() - 1);
    }
    
    // 2. Guardado en archivo externo en modo append (true como segundo parámetro)
    try {
      PrintWriter output = createWriter(dataPath(nombreArchivo));
      // Nota: Para append real en Processing, se suele abrir el archivo o reescribir. 
      // Usaremos loadStrings para acumular y guardar, o la clase nativa de Java si prefieres append puro.
      output.flush();
      output.close();
      
      // Forma robusta en Processing para Append usando java.io.FileWriter:
      java.io.FileWriter fw = new java.io.FileWriter(sketchPath(nombreArchivo), true);
      java.io.BufferedWriter bw = new java.io.BufferedWriter(fw);
      java.io.PrintWriter out = new java.io.PrintWriter(bw);
      out.println(timestamp);
      out.close();
      
    } catch (IOException e) {
      println("Error al guardar en el archivo de eventos: " + e.getMessage());
    }
  }
  
  // Dibuja un mini registro de eventos en la parte inferior de la ventana
  void dibujarHistorial(float x, float y, float ancho, float alto) {
    fill(20, 22, 26);
    stroke(70);
    rect(x, y, ancho, alto, 6);
    
    fill(255);
    textSize(12);
    textAlign(LEFT, TOP);
    text("Registro de Eventos Recientes (Historial):", x + 10, y + 8);
    
    textSize(10);
    fill(180);
    float offsetY = y + 26;
    for (String evento : historialMemoria) {
      text("• " + evento, x + 10, offsetY);
      offsetY += 14;
      if (offsetY > y + alto - 10) break; // Evita desbordar el panel
    }
  }
}
