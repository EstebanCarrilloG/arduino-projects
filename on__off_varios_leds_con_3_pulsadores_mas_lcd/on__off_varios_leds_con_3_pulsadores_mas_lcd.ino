#include <LiquidCrystal.h>

const int pula = A0;
const int pulab = A1;
const int selec = A2;
const int led1 = A3;
const int led2 = A4;
const int led3 = A5;
const int led4 = 8;


int pa = 0;
int pab = 0;
int se = 0;

int sp = 0;
int LBS = 0;
int LBSB = 0;
int LBSSE = 0;



int cl1 = 0;
int cl2 = 0;
int cl3 = 0;
int cl4 = 0;

int pos = 0;
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);



void setup() {
  pinMode(pula, INPUT);
  pinMode(pulab, INPUT);
  pinMode(selec, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  Serial.begin(9600);


  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("ENCENDER/APAGAR");
  lcd.setCursor(0, 1);
  lcd.print("LEDS");
  delay(1000);
  lcd.clear();
  pressi();

}

void loop() {

  lcd.setCursor(0, 1);
  lcd.print("1:  2:  3:  4:  ");
  seleccion();

  se = digitalRead(selec);


  if (se != LBSSE) {
    if (se == HIGH ) {

      if (sp == 1) {
        cl1++;
      }

      if (sp == 2) {
        cl2++;
      }

      if (sp == 3) {
        cl3++;
      }

      if (sp == 4) {
        cl4++;
      }
    }

  }

  LBSSE = se;
  if (cl1 % 2 == 0 ) {
    digitalWrite(led1, LOW);
    lcd.setCursor(2, 1);
    lcd.print("0");
    delay(5);
    cl1 = 0;
  } else {
    digitalWrite(led1, HIGH);
    lcd.setCursor(2, 1);
    lcd.print("1");
    delay(5);
  }

  if (cl2 % 2 == 0) {
    digitalWrite(led2, LOW);
    lcd.setCursor(6, 1);
    lcd.print("0");
    delay(5);
    cl2 = 0;
  } else {
    digitalWrite(led2, HIGH);
    lcd.setCursor(6, 1);
    lcd.print("1");
    delay(5);
  }

  if (cl3 % 2 == 0) {
    digitalWrite(led3, LOW);
    lcd.setCursor(10, 1);
    lcd.print("0");
    delay(5);
    cl3 = 0;
  } else {
    digitalWrite(led3, HIGH);
    lcd.setCursor(10, 1);
    lcd.print("1");
    delay(5);
  }


  if (cl4 % 2 == 0) {
    digitalWrite(led4, LOW);
    lcd.setCursor(14, 1);
    lcd.print("0");
    delay(5);
    cl4 = 0;
  } else {
    digitalWrite(led4, HIGH);
    lcd.setCursor(14, 1);
    lcd.print("1");
    delay(5);
  }
  delay(100);





}

void pressi() {
  while (1) {
    lcd.setCursor(0, 0);
    lcd.print("PRECIONE NEXT>");
    pa = digitalRead(pula);
    if (pa == HIGH) {
      break;
    }
  }
}


void seleccion() {

  pa = digitalRead(pula);
  pab = digitalRead(pulab);


  if (pa != LBS or pab != LBSB) {

    if (pa == HIGH) {
      sp++;
      Serial.println(sp);
      if (sp > 4) {
        sp = 4;
      }
      menu();
    }
    if (pab == HIGH) {
      sp--;
      Serial.println(sp);
      if (sp < 1) {
        sp = 1;
      }
      menu();
    }

    delay(50);
  }

  LBS = pa;
  LBSB = pab;
}

void menu() {

  switch (sp) {
    case 1:
      lcds();
    case 2:
      lcds();
    case 3:
      lcds();
    case 4:
      lcds();
  }
  delay(1);

}

void lcds() {
  lcd.setCursor(0, 0);
  lcd.print("<PREV  L   NEXT>");
  lcd.setCursor(8, 0);
  lcd.print(sp);
}
