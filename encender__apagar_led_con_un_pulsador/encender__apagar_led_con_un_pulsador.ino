/* 

* Código escrito por: Esteban Carrillo para EDEPTEC. 
* Página web: https://www.edeptec.com
* Facebook: @edeptec
* Youtube: https://youtube.com/c/EDEPTEC

*/

#define led 13
#define pulsador 2

byte conteo;
bool estadoPrevio;

void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(pulsador, INPUT);
}

void loop()
{

  bool estadoPulsador = digitalRead(pulsador);

  if (estadoPulsador  != estadoPrevio) {
    if (estadoPulsador == HIGH) {
      conteo++;

    }
  }
  delay(10);

  estadoPrevio = estadoPulsador;

  if (conteo % 2 == 0) {
    digitalWrite(13, LOW);
  } else {
    digitalWrite(13, HIGH);
  }

  Serial.println(conteo);
}
