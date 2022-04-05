/* 

* Código escrito por: Esteban Carrillo para EDEPTEC. 
* Página web: https://www.edeptec.com
* Facebook: @edeptec
* Youtube: https://youtube.com/c/EDEPTEC

*/

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
lcd.begin(16, 2); 
}

void loop() 
{ 
  int c = centi ();
  
  lcd.setCursor(0,0);
  lcd.print("TEMPERATURA:   C");
  lcd.setCursor(13,0);
  lcd.print(c);
  
}

float centi()
{
  int dato; 
  int c; 
  dato= analogRead(A0);
  c = (500.0 * dato)/1023;
  return(c); 
}
