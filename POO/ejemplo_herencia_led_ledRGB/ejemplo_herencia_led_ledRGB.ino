#include "Led.h"
#include "LedRGB.h"

// Un LED normal
Led ledSimple(9);

// Un LED RGB
LedRGB ledRGB(3, 5, 6);

void setup() {
  Serial.begin(9600);

  ledSimple.iniciar();
  ledRGB.iniciar();

  Serial.println("Sistema de LEDs con herencia inicializado");
}

void loop() {
  // Encender LED normal
  ledSimple.setBrillo(200);
  ledSimple.encender();
  delay(1000);
  ledSimple.apagar();
  delay(500);

  // LED RGB: mostrar colores básicos
  ledRGB.setColor(255, 0, 0); // Rojo
  delay(1000);
  ledRGB.setColor(0, 255, 0); // Verde
  delay(1000);
  ledRGB.setColor(0, 0, 255); // Azul
  delay(1000);

  ledRGB.apagar();
  delay(1000);
}