class InterfacePanel {
  float x, y, ancho, alto;
  
  InterfacePanel(float x, float y, float ancho, float alto) {
    this.x = x;
    this.y = y;
    this.ancho = ancho;
    this.alto = alto;
  }
  
  void dibujar(int estadoAlarma, int estadoPir, boolean[] estadosLuminarias) {
    fill(40, 44, 52);
    stroke(80);
    strokeWeight(2);
    rect(x, y, ancho, alto, 10);
    
    fill(255);
    textSize(20);
    textAlign(CENTER, TOP);
    text("PANEL DE CONTROL DOMÓTICO", x + ancho / 2, y + 15);
    
    fill(60, 64, 72);
    rect(x + 20, y + 60, ancho - 40, 80, 8);
    
    textSize(14);
    textAlign(LEFT, CENTER);
    fill(200);
    text("Estado del Sistema:", x + 40, y + 85);
    text("Sensor PIR:", x + 40, y + 115);
    
    if (estadoAlarma == 0) {
      fill(46, 204, 113); 
      text("DESARMADO", x + 180, y + 85);
    } else if (estadoAlarma == 1) {
      fill(52, 152, 219); 
      text("ARMADO", x + 180, y + 85);
    } else {
      fill(231, 76, 60); 
      text("¡ALARMA DISPARADA!", x + 180, y + 85);
    }
    
    if (estadoPir == 1) {
      fill(231, 76, 60);
      text("¡MOVIMIENTO DETECTADO!", x + 180, y + 115);
    } else {
      fill(149, 165, 166);
      text("Normal (Sin movimiento)", x + 180, y + 115);
    }
    
    fill(255);
    textSize(16);
    textAlign(CENTER, CENTER);
    text("Control de Luminarias", x + ancho / 2, y + 170);
    
    float botonAncho = (ancho - 60) / 4;
    float botonAlto = 60;
    
    for (int i = 0; i < 4; i++) {
      float posX = x + 20 + i * (botonAncho + 6);
      float posY = y + 200;
      
      if (estadosLuminarias[i]) {
        fill(241, 196, 15); 
        stroke(255);
      } else {
        fill(127, 140, 141); 
        stroke(100);
      }
      
      rect(posX, posY, botonAncho, botonAlto, 6);
      
      fill(0);
      textSize(12);
      textAlign(CENTER, CENTER);
      text("Luz " + (i + 1), posX + botonAncho / 2, posY + botonAlto / 2);
    }
  }
  
  int verificarClick(float mouseX, float mouseY) {
    float botonAncho = (ancho - 60) / 4;
    float botonAlto = 60;
    float posY = y + 200;
    
    for (int i = 0; i < 4; i++) {
      float posX = x + 20 + i * (botonAncho + 6);
      if (mouseX >= posX && mouseX <= posX + botonAncho && mouseY >= posY && mouseY <= posY + botonAlto) {
        return i; 
      }
    }
    return -1; 
  }
}
