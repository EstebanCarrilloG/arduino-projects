/* 

* Código escrito por: Esteban Carrillo para EDEPTEC. 
* Página web: https://www.edeptec.com
* Facebook: @edeptec
* Youtube: https://youtube.com/c/EDEPTEC

*/

#include <Keypad.h>
#include <LiquidCrystal.h>
#define led 3

int estado = 0;

int Pass1[4] = {2, 8, 3, 1};
int Pass2[5] = {4, 5, 7, 9, 2};
int Pass3[6] = {3, 8, 7, 5, 2, 3};
int A[6];
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {13, 12, 11, 10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad
char ABRIR;
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int ilosc;
int i = 0;
char key;
int codigo;
uint8_t  num;

int z;

void setup() {
  
  pinMode(led,OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  
}

void loop() {
  
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SELECCIONE EL");
  lcd.setCursor(0, 1);
  lcd.print("Nro DE DIGITOS");
  delay(100);
  i = 0;
  key = keypad.getKey();
  Serial.println(key);
  if (key != NO_KEY) {
    switch (key) {
      case '4':
        lcdd();     // your hand is on the sensor
        clave3();
        break;
      case '5':    // your hand is close to the sensor
        lcdd();
        clave3();
        break;
      case '6':    // your hand is a few inches from the sensor
        lcdd();
        clave3();
        break;
      default:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("ERROR");
        delay(600);



    }
  }
  delay(1);
}

void lcdd() {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  *BIENVENIDO*");
  lcd.setCursor(0, 1);
  lcd.print("INGRESE CLAVE ");
  lcd.print(key);
  delay(100);
}

void clave3() {


  while (true) {


    int Y = keypad.getKey();
    num = 0;
    if (Y) {
      codigo = Y;
      num = num * 10 + (codigo - 48);
      Serial.println(num);
      ilosc = ilosc + 1;

      Serial.println(ilosc);

      if (ilosc == 1)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("<CLAVE>");
        lcd.setCursor(0, 1);
        lcd.print("*");
        A[0] = num;
      }
      if (ilosc == 2)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("<CLAVE>");
        lcd.setCursor(0, 1);
        lcd.print("**");
        A[1] = num;
      }
      if (ilosc == 3)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("<CLAVE>");
        lcd.setCursor(0, 1);
        lcd.print("***");
        A[2] = num;
      }
      if (ilosc == 4)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("<CLAVE>");
        lcd.setCursor(0, 1);
        lcd.print("****");
        A[3] = num;
        z = 1;
      }

      if (ilosc == 5)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("<CLAVE>");
        lcd.setCursor(0, 1);
        lcd.print("*****");
        A[4] = num;
        z = 2 ;
      }
      if (ilosc == 6)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("<CLAVE>");
        lcd.setCursor(0, 1);
        lcd.print("******");
        A[5] = num;
        z = 3;
      }
      if ((z == 1 and key == '4') or (z == 2 and key == '5') or (z == 3 and key == '6')  )
      {
        delay(250);
        checkPassword();
        ilosc = 0;
      }
    }
    if (i == 1) {
      break;
    }
  }
}






void checkPassword()
{

  if ((A[0] == Pass1[0] and A[1] == Pass1[1] and A[2] == Pass1[2] and A[3] == Pass1[3]) or
      (A[0] == Pass2[0] and A[1] == Pass2[1] and A[2] == Pass2[2] and A[3] == Pass2[3] and A[4] == Pass2[4]) or
      (A[0] == Pass3[0] and A[1] == Pass3[1] and A[2] == Pass3[2] and A[3] == Pass3[3] and A[4] == Pass3[4] and A[5] == Pass3[5])) {
    Serial.println("Correcto");
    ilosc = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("CLAVE CORRECTA");
    digitalWrite(led,1);
    delay(1000);
    digitalWrite(led,0);
    
    i = 1;
    z = 0;
    key = 0;
  } else {

    ilosc = 0;
    Serial.println("Error");

    z = 0;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("CLAVE INCORRECTA");
    delay(2000);
    key = 0;
    i = 1;
  }
}


