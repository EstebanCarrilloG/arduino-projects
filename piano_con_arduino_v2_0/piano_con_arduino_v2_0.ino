#include "pitches.h"

#define speaker 8

#define p1 A0
#define p2 A1
#define p3 A2
#define p4 A3
#define p5 A4
#define p6 A5
#define p7 11
#define p8 6

#define pA 2
#define pB 12

boolean selecA;
boolean selecB;
boolean prevestA = 0;
boolean prevestB = 0;

short tiempo = 100;
byte S = 1 ;

// notes in the melody:
int nota[] = {
  NOTE_C2, //DO 0
  NOTE_D2, //RE 1
  NOTE_E2, //MI 2
  NOTE_F2, //FA 3
  NOTE_G2, //SOL 4
  NOTE_A2, //LA 5
  NOTE_B2, //SI 6
  NOTE_C3, // DO 7
  NOTE_D3, //RE 8
  NOTE_E3, //MI 9
  NOTE_F3, //FA 10
  NOTE_G3, //SOL 11
  NOTE_A3, //LA 12
  NOTE_B3, //SI 13
  NOTE_C4, // DO 14
  NOTE_D4, //RE 15
  NOTE_E4, //MI 16
  NOTE_F4, //FA 17
  NOTE_G4, //SOL 18
  NOTE_A4, //LA 19
  NOTE_B4, //SI 20
  NOTE_C5, //DO 21
  NOTE_D5, //RE 22
  NOTE_E5, //MI 23
  NOTE_F5, //FA 24
  NOTE_G5, //SOL 25
  NOTE_A5, //LA 26
  NOTE_B5, //SI 27
  NOTE_C6, // DO 28
  NOTE_D6, //RE 29
  NOTE_E6, //MI 30
  NOTE_F6, //FA 31
  NOTE_G6, //SOL 32
  NOTE_A6, //LA 33
  NOTE_B6, //SI 34
  NOTE_C7, // DO 35
  NOTE_D7, //RE 36
  NOTE_E7, //MI 37
  NOTE_F7, //FA 38
  NOTE_G7, //SOL 39
  NOTE_A7, //LA 40
  NOTE_B7, //SI 41
};

void setup() {
  Serial.begin(9600);
  pinMode(p1, INPUT);
  pinMode(p2, INPUT);
  pinMode(p3, INPUT);
  pinMode(p4, INPUT);
  pinMode(p5, INPUT);
  pinMode(p6, INPUT);
  pinMode(p7, INPUT);
  pinMode(p8, INPUT);

  pinMode(pA, INPUT);
  pinMode(pB, INPUT);

  pinMode(speaker, OUTPUT);

}

void comprovarB() {
  Serial.println(S);

  selecA = digitalRead(pA);
  selecB = digitalRead(pB);

  if (selecA != prevestA) {
    if (selecA == 1) {
      S++;
    }
    delay(50);
  }

  prevestA = selecA;

  if (selecB != prevestB) {
    if (selecB == 1) {
      S--;
    }
    delay(50);
  }

  prevestB = selecB;

  if (S > 6 and S < 8 or S == 0  ) {
    S = 1;
  }
}
void loop() {
  comprovarB();
  bool pul7 = digitalRead(p7);
  bool pul8 = digitalRead(p8);

  ////////////////////////////////////////
  if (digitalRead(p1)) {
    int x;
    switch (S) {
      case 1: x = 0; break;
      case 2: x = 7; break;
      case 3: x = 14; break;
      case 4: x = 21; break;
      case 5: x = 28; break;
      case 6: x = 35; break;
    }
    delay(1);
    tone(speaker, nota[x], tiempo);
  }
  ////////////////////////////////////////
  if (digitalRead(p2)) {
    int x;
    switch (S) {
      case 1: x = 1; break;
      case 2: x = 8; break;
      case 3: x = 15; break;
      case 4: x = 22; break;
      case 5: x = 29; break;
      case 6: x = 36; break;
    }
    delay(1);
    tone(speaker, nota[x], tiempo);
  }

  ////////////////////////////////////////
  if (digitalRead(p3)) {
    int x;
    switch (S) {
      case 1: x = 2; break;
      case 2: x = 9; break;
      case 3: x = 16; break;
      case 4: x = 23; break;
      case 5: x = 30; break;
      case 6: x = 37; break;
    }
    delay(1);
    tone(speaker, nota[x], tiempo);
  }
  ////////////////////////////////////////
  if (digitalRead(p4)) {
    int x;
    switch (S) {
      case 1: x = 3; break;
      case 2: x = 10; break;
      case 3: x = 17; break;
      case 4: x = 24; break;
      case 5: x = 31; break;
      case 6: x = 38; break;
    }
    delay(1);
    tone(speaker, nota[x], tiempo);
  }
  ////////////////////////////////////////
  if (digitalRead(p5)) {
    int x;
    switch (S) {
      case 1: x = 4; break;
      case 2: x = 11; break;
      case 3: x = 18; break;
      case 4: x = 25; break;
      case 5: x = 32; break;
      case 6: x = 39; break;
    }
    delay(1);
    tone(speaker, nota[x], tiempo);
  }
  ////////////////////////////////////////
  if (digitalRead(p6)) {
    int x;
    switch (S) {
      case 1: x = 5; break;
      case 2: x = 12; break;
      case 3: x = 19; break;
      case 4: x = 26; break;
      case 5: x = 33; break;
      case 6: x = 40; break;
    }
    delay(1);

    tone(speaker, nota[x], tiempo);
  }
  ////////////////////////////////////////

  if (digitalRead(p7)) {
    int x;
    switch (S) {
      case 1: x = 6; break;
      case 2: x = 13; break;
      case 3: x = 20; break;
      case 4: x = 27; break;
      case 5: x = 34; break;
      case 6: x = 41; break;
    }
    delay(1);
    tone(speaker, nota[x], tiempo);
  }
  ////////////////////////////////////////
  if (digitalRead(p8)) {
    int x;
    switch (S) {
      case 1: x = 7; break;
      case 2: x = 14; break;
      case 3: x = 21; break;
      case 4: x = 28; break;
      case 5: x = 35; break;
    }
    delay(1);
    tone(speaker, nota[x], tiempo);
  }
}
