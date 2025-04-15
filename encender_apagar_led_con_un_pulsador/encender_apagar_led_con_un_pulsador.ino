/*

  Código escrito por: Esteban Carrillo para EDEPTEC.
  Página web: https://www.edeptec.com
  Facebook: @edeptec
  Youtube: https://youtube.com/c/EDEPTEC

*/

#define led 13 // led en el pin 13
#define pulsador 2 // pulsador en el pin 2

bool estadoDelLed = 0; // Variable para controlar el estado del led
bool estadoPrevio = 0; // Variable para controlar el estado previo del pulsador

void setup()
{
  pinMode(led, OUTPUT); // led como salida
  pinMode(pulsador, INPUT);// pulsador como entrada
  digitalWrite(led, 0); // led apagado por defecto
}

void loop()
{
  bool estadoPulsador = digitalRead(pulsador); // Estado lógico del pulsador

  if(estadoPulsador  != estadoPrevio && estadoPulsador == HIGH) // Implementación antirrebote && si se presiona el pulsador: 
    digitalWrite(led, estadoDelLed = !estadoDelLed); // Se enciende o apaga el led dependiendo de el valor de la variable estadoDelLed

  delay(10); // Pausa de 10ms
  estadoPrevio = estadoPulsador; // Implementación antirrebote
   
}