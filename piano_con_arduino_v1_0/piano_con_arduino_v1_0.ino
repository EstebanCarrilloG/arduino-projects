/* 

* Código escrito por: Esteban Carrillo para EDEPTEC. 
* Página web: https://www.edeptec.com
* Facebook: @edeptec
* Youtube: https://youtube.com/c/EDEPTEC

*/

#include "pitches.h"
#define speaker 8

#define p1 A0
#define p2 A1
#define p3 A2
#define p4 A3
#define p5 A4
#define p6 A5
#define p7 2
#define p8 3

short tiempo = 8;

// notes in the melody:
int nota[] = {
  NOTE_C3, //DO 0
  NOTE_D3, //RE 1
  NOTE_E3, //MI 2
  NOTE_F3, //FA 3
  NOTE_G3, //SOL 4
  NOTE_A3, //LA 5
  NOTE_B3, //SI 6
  NOTE_C4, // DO 7

};


void setup() {

  pinMode(p1, INPUT);
  pinMode(p2, INPUT);
  pinMode(p3, INPUT);
  pinMode(p4, INPUT);
  pinMode(p5, INPUT);
  pinMode(p6, INPUT);
  pinMode(p7, INPUT);
  pinMode(p8, INPUT);
  pinMode(speaker, OUTPUT);

}


void loop() {

  if (digitalRead(p1)) {
    tone(speaker, nota[0], tiempo);
  }
  if (digitalRead(p2)) {
    tone(speaker, nota[1], tiempo);
  }
  if (digitalRead(p3)) {
    tone(speaker, nota[2], tiempo);
  }
  if (digitalRead(p4)) {
    tone(speaker, nota[3], tiempo);
  }
  if (digitalRead(p5)) {
    tone(speaker, nota[4], tiempo);
  }
  if (digitalRead(p6)) {
    tone(speaker, nota[5], tiempo);
  }
  if (digitalRead(p7) {
    tone(speaker, nota[6], tiempo);
  }
  if (digitalRead(p8) {
    tone(speaker, nota[7], tiempo);
  }
}
