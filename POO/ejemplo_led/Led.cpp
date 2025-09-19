// Led.cpp - Implementación
#include "Led.h"

// Constructor
Led::Led(int pinLed) {
  pin = pinLed;
  estado = false;
  brillo = 255;  // Brillo máximo por defecto
}

// Inicializar pin
void Led::iniciar() {
  pinMode(pin, OUTPUT);
  apagar();
}

// Encender LED
void Led::encender() {
  estado = true;
  analogWrite(pin, brillo);
}

// Apagar LED
void Led::apagar() {
  estado = false;
  analogWrite(pin, 0);
}

// Cambiar estado
void Led::toggle() {
  if (estado) apagar();
  else encender();
}

// Ajustar brillo
void Led::setBrillo(int nivel) {
  brillo = constrain(nivel, 0, 255);
  if (estado) analogWrite(pin, brillo);
}

// Parpadear
void Led::parpadear(int veces, int duracion) {
  for (int i = 0; i < veces; i++) {
    toggle();
    delay(duracion);
  }
}

// Obtener estado
bool Led::getEstado() {
  return estado;
}