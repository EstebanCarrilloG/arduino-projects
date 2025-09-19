// sketch_principal.ino
#include "Led.h"


// Crear instancias de LED para diferentes colores
Led ledRojo(9);    // LED rojo en pin 9 (PWM)
Led ledVerde(10);  // LED verde en pin 10 (PWM)
Led ledAzul(11);   // LED azul en pin 11 (PWM)


void setup() {
  Serial.begin(9600);

  // Inicializar los LEDs
  ledRojo.iniciar();
  ledVerde.iniciar();
  ledAzul.iniciar();

  Serial.println("Sistema de LEDs inicializado");
}

void loop() {
  // Secuencia de LEDs con diferentes brillos
  ledRojo.setBrillo(255);
  ledRojo.encender();
  delay(1000);

  // Mostrar el estado del LED rojo
  Serial.print("Estado LED rojo: ");
  Serial.println(ledRojo.getEstado() ? "ENCENDIDO" : "APAGADO");

  ledVerde.setBrillo(150);
  ledVerde.encender();
  delay(1000);

  ledAzul.setBrillo(80);
  ledAzul.encender();
  delay(1000);

  // Apagar todos los LEDs
  ledRojo.apagar();
  ledVerde.apagar();
  ledAzul.apagar();
  delay(500);

  // Mostrar el estado del LED rojo
  Serial.print("Estado LED rojo: ");
  Serial.println(ledRojo.getEstado() ? "ENCENDIDO" : "APAGADO");

  // Hacer parpadear el LED verde 3 veces
  ledVerde.parpadear(3, 300);
  delay(1000);
}