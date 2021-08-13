#define led 3 // Pin donde va conectado el led
#define pot A0 // Pin donde va conectado el potenciometro
 
void setup() {
 
 pinMode(led,OUTPUT); // Declaramos entradas y salidas
 pinMode(pot,INPUT);
 
 
}
 
void loop() {
 
  int pwm; // Declaramos una variable, en esta variable se almacenan los valores que nos entrega la función map
  pwm = map(analogRead(pot), 0, 1024, 0, 255);
 
  analogWrite(led,pwm); // Encendemos el led con el valor del pwm que nos envía le función map
 
  delay(100); // agregamos una pequeña pausa
 
}
