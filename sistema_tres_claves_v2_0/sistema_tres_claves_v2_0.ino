/*
  Código escrito por: Esteban Carrillo para EDEPTEC.
  Página web: https://www.edeptec.com
  Facebook: @edeptec
  Youtube: https://youtube.com/c/EDEPTEC
*/
#include <Keypad.h>
#include <LiquidCrystal.h>
#define greenLed A4
#define redLed A5

const int rs = 3, en = 4, d4 = A0, d5 = A1, d6 = A2, d7 = A3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {12, 11, 10, 9};
byte colPins[COLS] = {8, 7, 6, 5};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

String pass[3] = {"2A3B", "4C72D", "A8C5D3"};

void setup() {
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  digitalWrite(greenLed, 1);
  digitalWrite(redLed, 1);
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  //--- 1 ---
  lcd.setCursor(0, 0);
  lcd.print("SELECCIONE CLAVE");
  lcd.setCursor(2, 1);
  lcd.print("(A) (B) (C)");
  //--- 2 ---
  char key = keypad.getKey();
  //--- 3 ---
  if (key != NO_KEY) {
    switch (key) {
      case 'A':
        inputPassword(pass[0]);
        break;
      case 'B':
        inputPassword(pass[1]);
        break;
      case 'C':
        inputPassword(pass[2]);
        break;
      default:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("ERROR");
        delay(600);
        lcd.clear();
    }
  }
  delay(10);
}

void inputPassword(String password) {
  String keyString = ""; // 1
  byte spaceJump = 0;// 2
  printMsg(password.length()); // 3
  while (true) { // 4
    char keyPressed = keypad.getKey();
    if (keyPressed != NO_KEY) {
      keyString += keyPressed;
      lcd.setCursor(spaceJump, 1);
      lcd.print('*');
      spaceJump++;
      blinkLed(greenLed, 5, 10);
    }
    boolean state = checkPassword(keyString, password); // 5
    delay(50);
    if (state == true) { // 6
      lcd.clear();
      break;
    }
  }
}

void printMsg(int n) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("INGRESE LA CLAVE");
  lcd.setCursor(0, 1);
  lcd.print("DE ");
  lcd.print(n);
  lcd.print(" DIGITOS");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CLAVE:");
}

boolean checkPassword(String keyString, String password) {
  if (keyString.length() == password.length() ) { //5.1
    lcd.clear();
    lcd.home();
    if (keyString.equals(password)) {
      lcd.print("CLAVE CORRECTA");
      digitalWrite(greenLed, 0);
      delay(1000);
      digitalWrite(greenLed, 1);
    } else {
      lcd.print("CLAVE INCORRECTA");
      blinkLed(redLed, 100, 3);
      delay(1000);
    }
    return true;
  }
  return false; // 5.2
}

void blinkLed(int led, byte pause, byte n) {
  for (int i = 0; i < n; i++) {
    digitalWrite(led, 0);
    delay(pause);
    digitalWrite(led, 1);
    delay(pause);
  }
}
