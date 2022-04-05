/* 

* Código escrito por: Esteban Carrillo para EDEPTEC. 
* Página web: https://www.edeptec.com
* Facebook: @edeptec
* Youtube: https://youtube.com/c/EDEPTEC

*/

#define t1 A1
#define t2 A2
#define t3 A3
#define lm35 A0
#define calefactor 6
#define ventilador 7


#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

boolean menos = 0;
boolean mas = 0;

boolean select = 0;
short tempmin = 10;
short tempmax = 21;
byte i;
byte x;
int x1;
int dato = 0;
int c;

boolean estadoAnt = 0;

void setup() {

  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(t1, INPUT);
  pinMode(t2, INPUT);
  pinMode(t3, INPUT);
  pinMode(lm35, INPUT);
  pinMode(calefactor, OUTPUT);
  pinMode(ventilador, OUTPUT);
  digitalWrite(calefactor, LOW);
  digitalWrite(ventilador, LOW);
  tempval();
}



void loop() {

  if (c <= tempmin) {
    digitalWrite(calefactor, HIGH);
    digitalWrite(ventilador, LOW);
  } else if (c >= tempmax) {
    digitalWrite(calefactor, LOW);
    digitalWrite(ventilador, HIGH);
  } else {
    digitalWrite(ventilador, LOW);
    digitalWrite(calefactor, LOW);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T.L ");
  lcd.print(" T.Act ");
  lcd.print("T.H");
  lcd.setCursor(0, 1);
  lcd.print(tempmin);
  lcd.print("oC ");
  lcd.print(c);
  lcd.print("oC  ");
  lcd.print(tempmax);
  lcd.print("oC");
  delay(100);

  for (x1 = 0; x1 < 1000; x1++) {
    tempval();
    teclas();

    Serial.println(x1);

    if (i == 1) {
      temperaturaMin();
    }
    if (i == 2) {
      temperaturaMax();
    }
  }
}

void tempval() {
  dato = analogRead(lm35);
  c = (500.0 * dato) / 1023;
}

void teclas() {

  menos = digitalRead(t2);
  mas = digitalRead(t3);
  select = digitalRead(t1);

  if (select != estadoAnt) {
    if (select == HIGH) {
      i++;
    }
    delay(50);
  }
  estadoAnt = select;

  if (i == 3 ) {
    i = 1;
  }
}

void temperaturaMin() {
  lcd.clear();
  if (i == 1) {

    for (x = 0 ; x < 30; x++) {
      x1 = 999;
      msg1();
      lcd.print(" Tmin");
      delay(10);
      teclas();

      if (i == 2) {
        temperaturaMax();
      }

      if (mas == HIGH) {
        delay(100 );

        while (true) {
          teclas();
          if (mas == HIGH ) {
            tempmin++;
          }

          if (menos == HIGH) {
            tempmin--;
          }

          if (select == HIGH) {
            i = 0;
            x = 29;
            x1 = 999;
            break;
          }

          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Set temp min");
          lcd.setCursor(0, 1);
          lcd.print(tempmin);
          lcd.print(" oC");
          delay(100);
        }
      }
      delay(1);
    }
    i = 0;
  }
}

void temperaturaMax() {
  lcd.clear();
  if (i == 2) {

    for (x = 0 ; x < 30; x++) {
      x1 = 999;

      msg1();
      lcd.print(" Tmax");
      Serial.println(i);
      delay(10);
      teclas();

      if (i == 1) {
        temperaturaMin();
      }

      if (mas == HIGH) {
        delay(100);
        while (true) {
          teclas();

          if (mas == HIGH ) {
            tempmax++;
          }

          if (menos == HIGH) {
            tempmax--;
          }

          if (select == HIGH) {
            i = 0;
            x = 29;
            x1 = 999;
            break;
          }

          if (tempmax > 30) {
            tempmax = 30;
          }

          if (tempmax < 20) {
            tempmax = 20;
          }

          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Set temp max");
          lcd.setCursor(0, 1);
          lcd.print(tempmax);
          lcd.print(" oC");
          delay(100);
        }
      }
      delay(1);
    }
    i = 0;
  }
}

void msg1() {
  lcd.setCursor(0, 0);
  lcd.print("Presione + para");
  lcd.setCursor(0, 1);
  lcd.print("Modificar");
}
