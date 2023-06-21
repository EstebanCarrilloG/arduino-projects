#include <EEPROM.h>

byte pinPulsador = 2;
byte estadoAnterior = 0;

float rValue;

float valorAlmacenado = 0;

void setup() {

  float f = 4000000;  //Variable to store data read from EEPROM.
  int eeAddress = 0;  //EEPROM address to start reading from

  Serial.begin(9600);
  EEPROM.put(eeAddress, f);
  EEPROM.get(eeAddress, valorAlmacenado);
}

void loop() {
  boolean btnState = digitalRead(pinPulsador);
  Serial.println(btnState);

  if (btnState != estadoAnterior) {
    if (btnState == HIGH) {
      valorAlmacenado++;

      delay(25);
  	EEPROM.put(0, valorAlmacenado);	    
    }
  }
  estadoAnterior = btnState;
  
  EEPROM.get(0,rValue);

  Serial.println(String(rValue,0));

  delay(10);
}