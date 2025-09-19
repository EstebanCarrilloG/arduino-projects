#include "LedRGB.h"
#include "Led.h"

// Constructor: inicializa con 3 pines
LedRGB::LedRGB(int r, int g, int b) : Led(-1) {  
  // "-1" porque la clase base espera un pin, pero aquí usamos 3
  pinR = r;
  pinG = g;
  pinB = b;
}

void LedRGB::iniciar() {
  pinMode(pinR, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinB, OUTPUT);
  apagar();
}

void LedRGB::setColor(int rojo, int verde, int azul) {
  analogWrite(pinR, constrain(rojo, 0, 255));
  analogWrite(pinG, constrain(verde, 0, 255));
  analogWrite(pinB, constrain(azul, 0, 255));
}

void LedRGB::apagar() {
  analogWrite(pinR, 0);
  analogWrite(pinG, 0);
  analogWrite(pinB, 0);
}