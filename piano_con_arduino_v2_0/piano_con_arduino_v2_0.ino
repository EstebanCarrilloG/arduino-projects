/* 

* Código escrito por: Esteban Carrillo para EDEPTEC. 
* Página web: https://www.edeptec.com
* Facebook: @edeptec
* Youtube: https://youtube.com/c/EDEPTEC

*/

#include "pitches.h"

#define altavoz 8

// Pulsadores principales (teclas musicales)
int pulsadores[] = { A0, A1, A2, A3, A4, A5, 11, 6 };

int pulsadoresLength = sizeof(pulsadores) / sizeof(pulsadores[0]);

// Pulsadores para cambio de escala
#define pSubir 2
#define pBajar 12

// Variables de control
boolean estadoAnteriorSubir = 0;
boolean estadoAnteriorbajar = 0;
short tiempo = 100;
byte escala = 1;

//Notas desde C2 hasta B8 organizadas secuencialmente
int nota[] = {
  NOTE_C2,  //DO 0
  NOTE_D2,  //RE 1
  NOTE_E2,  //MI 2
  NOTE_F2,  //FA 3
  NOTE_G2,  //SOL 4
  NOTE_A2,  //LA 5
  NOTE_B2,  //SI 6
  NOTE_C3,  // DO 7
  NOTE_D3,  //RE 8
  NOTE_E3,  //MI 9
  NOTE_F3,  //FA 10
  NOTE_G3,  //SOL 11
  NOTE_A3,  //LA 12
  NOTE_B3,  //SI 13
  NOTE_C4,  // DO 14
  NOTE_D4,  //RE 15
  NOTE_E4,  //MI 16
  NOTE_F4,  //FA 17
  NOTE_G4,  //SOL 18
  NOTE_A4,  //LA 19
  NOTE_B4,  //SI 20
  NOTE_C5,  //DO 21
  NOTE_D5,  //RE 22
  NOTE_E5,  //MI 23
  NOTE_F5,  //FA 24
  NOTE_G5,  //SOL 25
  NOTE_A5,  //LA 26
  NOTE_B5,  //SI 27
  NOTE_C6,  // DO 28
  NOTE_D6,  //RE 29
  NOTE_E6,  //MI 30
  NOTE_F6,  //FA 31
  NOTE_G6,  //SOL 32
  NOTE_A6,  //LA 33
  NOTE_B6,  //SI 34
  NOTE_C7,  // DO 35
  NOTE_D7,  //RE 36
  NOTE_E7,  //MI 37
  NOTE_F7,  //FA 38
  NOTE_G7,  //SOL 39
  NOTE_A7,  //LA 40
  NOTE_B7,  //SI 41
};

void setup() {
  Serial.begin(9600);

  // Configurar pines de los pulsadores como entradas
  for (int i = 0; i < pulsadoresLength; i++) {
    pinMode(pulsadores[i], INPUT);
  }

  pinMode(pSubir, INPUT);
  pinMode(pBajar, INPUT);

  // Configurar pin del altavoz como salida
  pinMode(altavoz, OUTPUT);
}

void comprovarB() {
  bool subir = digitalRead(pSubir);
  bool bajar = digitalRead(pBajar);

  // Detectar pulsación en botón SUBIR
  if (subir != estadoAnteriorSubir) {
    if (subir == 1) {
      escala++;  // Subir a escala superior
    }
    delay(50);  // Anti-rebote
  }
  estadoAnteriorSubir = subir;

  // Detectar pulsación en botón BAJAR
  if (bajar != estadoAnteriorbajar) {
    if (bajar == 1) {
      escala--;  // Bajar a escala inferior
    }
    delay(50);  // Anti-rebote
  }
  estadoAnteriorbajar = bajar;
  // Limitar el rango entre 1 y 6 escalas
  escala = (escala > 6) ? 6 : (escala < 1) ? 1
                                           : escala; // Limitar el rango
}
void loop() {

  comprovarB();  // Verificar cambios de escala

  for (int i = 0; i < pulsadoresLength; i++) { // Recorrer los pulsadores
    if (digitalRead(pulsadores[i])) { // Si se presiona un pulsador
      int x;  // Variable auxiliar
      switch (escala) { // Dependiendo de la escala, se selecciona la nota correspondiente
        case 1: x = i + 0; break; // i + 0 es la primera nota de la escala
        case 2: x = i + 7; break; // i + 7 es la segunda nota de la escala
        case 3: x = i + 14; break;
        case 4: x = i + 21; break;
        case 5: x = i + 28; break;
        case 6: x = i + 35; break;
      }
      delay(1);
      tone(altavoz, nota[x], tiempo); // Reproducir la nota
    }
  }
}
