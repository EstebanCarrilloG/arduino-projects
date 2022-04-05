/* 

* Código escrito por: Esteban Carrillo para EDEPTEC. 
* Página web: https://www.edeptec.com
* Facebook: @edeptec
* Youtube: https://youtube.com/c/EDEPTEC

*/

#include<LiquidCrystal.h>
#define   pintrig  7
#define   pineco   6
LiquidCrystal lcd(12,11,5,4,3,2);

int tiempo;


void setup() {
  lcd.begin(16,2);
  pinMode(pintrig,OUTPUT);
  pinMode(pineco,INPUT);
}

void loop() {
  digitalWrite(pintrig,LOW);
  delayMicroseconds(2);
  digitalWrite(pintrig,HIGH);
  delayMicroseconds(10);
  digitalWrite(pintrig,LOW);

  tiempo = pulseIn(pineco,HIGH);
   int distancia= (tiempo/2)/29;


  if (distancia <= 2||distancia > 500)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Distancia");
    lcd.setCursor(0,1);
    lcd.print("excedida");
    
  }
  else
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("LA DISTANCIA:");
    lcd.setCursor(0,1);
    lcd.print(distancia);
    lcd.print("  cm");
    
    delay (500);
  }
}
