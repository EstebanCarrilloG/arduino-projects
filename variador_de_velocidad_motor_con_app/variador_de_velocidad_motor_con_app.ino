/* 

* Código escrito por: Esteban Carrillo para EDEPTEC. 
* Página web: https://www.edeptec.com
* Facebook: @edeptec
* Youtube: https://youtube.com/c/EDEPTEC

*/

#define pwmA  3
#define motorinA  4
#define motorinB  5
#define stby  6
//

// en esta variable almacenamos el valor que nos llega desde la aplicacion
// el valor del slider
int velocidad = 0;

void setup() {
  // inicializamos el monitor serial
  Serial.begin(9600);
  // declaramos entradas y salidas//
  pinMode(pwmA, OUTPUT);
  pinMode(motorinA, OUTPUT);
  pinMode(motorinB, OUTPUT);
  pinMode(stby, OUTPUT);
}

void loop() {

  //Si recibimos datos desde la aplicación entonces:
  if (Serial.available() > 0) {
    // la variable velocidad va a almacenar esos datos.
    velocidad = Serial.read();
  }
  digitalWrite(stby, 1); // activamos el puente h
  // enviamos en valor de la variable velocidad al pin PWM del puente h
  analogWrite(pwmA, velocidad);
  // encendemos el motor//
  digitalWrite(motorinA, 1);
  digitalWrite(motorinB, 0);
  // imprimimos la velocidad en el monitor serial//
  Serial.print("PWM:");
  Serial.println(velocidad);
}
