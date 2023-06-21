#include <EEPROM.h>

byte pinPulsador = 2;
byte estadoAnterior = 0;

float valorAlmacenado = 0;

void setup() {

  float f = 4000000;  //Variable to store data read from EEPROM.
  int eeAddress = 0;  //EEPROM address to start reading from

  Serial.begin(9600);
  EEPROM.put(eeAddress, f);
  valorAlmacenado = EEPROM.get(0, fg);
}

void loop() {
  boolean btnState = digitalRead(pinPulsador);


  Serial.println(btnState);

  if (btnState != estadoAnterior) {
    if (btnState == HIGH) {
      valorAlmacenado++;

      delay(25);
      EEPROM.update(0, valorAlmacenado);
      Serial.println(valorAlmacenado);
    }
  }
  estadoAnterior = btnState;

  delay(10);
}