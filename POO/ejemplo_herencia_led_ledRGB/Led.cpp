#include "Led.h"

// Constructor
Led::Led(int pinLed) {
  pin = pinLed;
  estado = false;
  brillo = 255;
}

void Led::iniciar() {
  pinMode(pin, OUTPUT);
  apagar();
}

void Led::encender() {
  estado = true;
  analogWrite(pin, brillo);
}

void Led::apagar() {
  estado = false;
  analogWrite(pin, 0);
}

void Led::setBrillo(int nivel) {
  brillo = constrain(nivel, 0, 255);
  if (estado) {
    analogWrite(pin, brillo);
  }
}

bool Led::getEstado() {
  return estado;
}