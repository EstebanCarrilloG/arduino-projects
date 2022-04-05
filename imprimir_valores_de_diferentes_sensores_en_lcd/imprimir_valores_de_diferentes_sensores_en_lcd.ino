/* 

* Código escrito por: Esteban Carrillo para EDEPTEC. 
* Página web: https://www.edeptec.com
* Facebook: @edeptec
* Youtube: https://youtube.com/c/EDEPTEC

*/

#include <LiquidCrystal.h>
#define s1 A0
#define s2 A1
#define s3 A2

const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int lect1;
int lect2;
int lect3;
int n;
short sensor[4];
void setup() {

  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
}

void loop()
{
  n++;
  obtenervalores();
  Serial.print("Sensor");
  Serial.print(n);
  Serial.print(":");
  Serial.println(sensor[n]);

  Serial.println("---------------");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Lectura valores");

  lcd.setCursor(0, 1);
  lcd.print("S");
  lcd.print(n);
  lcd.print(":");
  lcd.print(sensor[n]);
  delay(200);

  if (n == 3 ) {
    n = 0;
  }
}

void obtenervalores() {
  sensor[1] = analogRead(s1);
  sensor[2] = analogRead(s2);
  sensor[3] = analogRead(s3);
}
