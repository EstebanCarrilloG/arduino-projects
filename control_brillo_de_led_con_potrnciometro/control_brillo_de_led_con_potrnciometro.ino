/* 

* Código escrito por: Esteban Carrillo para EDEPTEC. 
* Página web: https://www.edeptec.com
* Facebook: @edeptec
* Youtube: https://youtube.com/c/EDEPTEC

*/

#define pinLed 3             // Pin donde va conectado el led
#define pinPotenciometro A0  // Pin donde va conectado el potenciometro

void setup() {
  pinMode(led, OUTPUT);  // Declaramos entradas y salidas
  pinMode(pinPotenciometro, INPUT);
}

void loop() {

  int pwm;  // Declaramos una variable, en esta variable se almacenan los valores que nos entrega la función map
  pwm = map(analogRead(pinPotenciometro), 0, 1024, 0, 255);

  analogWrite(pinLed, pwm);  // Encendemos el led con el valor del pwm que nos envía le función map

  delay(100);  // agregamos una pequeña pausa
}
