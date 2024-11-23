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
#define relay 2

const int rs = 3, en = 4, d4 = A0, d5 = A1, d6 = A2, d7 = A3; // Pines del LCD
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {12, 11, 10, 9}; //pines de filas del teclado
byte colPins[COLS] = {8, 7, 6, 5}; //pines de columnas del teclado

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //

String pass[3] = {"2A*B", "4#72D", "A8#*5D"}; // Claves


/**
   Inicializa los pines del led verde y rojo como salidas,
   se encarga de apagarlos y de inicializar el LCD.
*/
void setup() {
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(greenLed, 0);
  digitalWrite(redLed, 0);
  digitalWrite(relay, 0);

  lcd.begin(16, 2);
}

/**
   El loop principal del programa.

   1. Muestra en el lcd el mensaje "SELECCIONE CLAVE" y las opciones (A) (B) (C)
   2. Lee la tecla pulsada
   3. Si se pulso una tecla, dependiendo de la tecla puesta, pide el password
      correspondiente y lo valida. Si no es correcto, muestra un error en el lcd.

   En cualquier caso, espera 10ms antes de seguir.
*/
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

/**
   Pide al usuario que ingrese una clave y la valida.

   1. Inicializa una cadena vacía para almacenar la clave ingresada.
   2. Inicializa un contador para saltar espacios en el lcd.
   3. Muestra en el lcd el mensaje "INGRESE CLAVE" y el numero de caracteres
      que debe tener la clave.
   4. Espera a que el usuario presione una tecla, si se presiono una tecla
      la agrega a la cadena de caracteres.
*/
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
      blinkLed(greenLed, 100, 1);
    }
    boolean state = checkPassword(keyString, password); // 5
    delay(50);
    if (state == true) { // 6
      lcd.clear();
      break;
    }
  }
}


/**
   Muestra en el lcd el mensaje "INGRESE LA CLAVE" y el numero de caracteres
   que debe tener la clave.

   @param n Numero de caracteres que debe tener la clave
*/

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

/**
   Compara la clave ingresada por el usuario con la clave correcta.
   * Si la clave ingresada es igual a la clave seleccionada,
   muestra en el lcd que la clave es correcta y activa el relay.  

   @param keyString La clave ingresada por el usuario.
   @param password La clave correcta.

   @return true si el numero de caracteres ingresados es igual al numero de caracteres de la clave, false en caso contrario.
*/
boolean checkPassword(String keyString, String password) {
  if (keyString.length() == password.length() ) {
    lcd.clear();
    lcd.home();
    if (keyString.equals(password)) {
      lcd.print("CLAVE CORRECTA");
      blinkLed(greenLed, 1000, 1);
      digitalWrite(relay, 1);
      delay(300);
      digitalWrite(relay, 0);
    } else {
      lcd.print("CLAVE INCORRECTA");
      blinkLed(redLed, 100, 3);
      delay(1000);
    }
    return true;
  }
  return false;
}


/**
   Hace parpadear un led durante un numero determinado de veces.

   @param led El pin digital al que esta conectado el led.
   @param pause El tiempo en milisegundos que se enciende o apaga el led.
   @param n El numero de veces que se hara parpadear el led.
*/
void blinkLed(int led, byte pause, byte n) {
  for (int i = 0; i < n; i++) {
    digitalWrite(led, 0);
    delay(pause);
    digitalWrite(led, 1);
    delay(pause);
  }
  digitalWrite(led, 0);
}
