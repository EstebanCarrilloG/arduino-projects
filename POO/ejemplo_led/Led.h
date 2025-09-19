// Led.h - Archivo de cabecera
#ifndef LED_H
#define LED_H

#include <Arduino.h>

class Led {
private:
  int pin;      // Pin del LED
  bool estado;  // Estado actual (true=encendido, false=apagado)
  int brillo;   // Nivel de brillo (0-255)

public:
  // Constructor
  Led(int pinLed);

  // Métodos públicos
  void iniciar();
  void encender();
  void apagar();
  void toggle();
  void setBrillo(int nivel);
  void parpadear(int veces, int duracion);
  bool getEstado();
};
#endif