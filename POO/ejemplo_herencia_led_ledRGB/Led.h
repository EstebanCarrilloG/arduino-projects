#ifndef LED_H
#define LED_H

#include <Arduino.h>

class Led {
protected:
  int pin;      // Pin del LED
  bool estado;  // Estado actual
  int brillo;   // Nivel de brillo (0-255)

public:
  // Constructor
  Led(int pinLed);

  // Métodos públicos
  virtual void iniciar();
  virtual void encender();
  virtual void apagar();
  void setBrillo(int nivel);
  bool getEstado();
};

#endif