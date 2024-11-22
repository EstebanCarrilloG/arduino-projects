/*
  Código escrito por: Esteban Carrillo para EDEPTEC.
  Página web: https://www.edeptec.com
  Facebook: @edeptec
  Youtube: https://youtube.com/c/EDEPTEC
*/

#include <LiquidCrystal.h>

const int pulNext = A0;
const int pulPrev = A1;
const int pulOnOff = A2;
byte leds[] = {A3, A4, A5, 8};

byte ledActual = 1;
int estadoPrevioPulNext = 0;
int estadoPrevioPulPrev = 0;
bool estadoPrevio = 0;

bool estadoDeLeds[] = {0, 0, 0, 0};

const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

/**
 * Configura los pines de los pulsadores como entradas, y los pines de los
 * LEDs como salidas. Inicializa la comunicación serial y el LCD.
 *
 * Muestra en el LCD el texto de bienvenida y espera 1 segundo.
 */
void setup() {
  pinMode(pulNext, INPUT);
  pinMode(pulPrev, INPUT);
  pinMode(pulOnOff, INPUT);

  for (byte i = 0 ; i < sizeof(leds); i++) {
    pinMode(leds[i], OUTPUT);
  }

  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("ENCENDER/APAGAR");
  lcd.setCursor(0, 1);
  lcd.print("LEDS");
  delay(1000);
  lcd.clear();
}

/**
 * El bucle principal del programa.
 *
 * En este bucle se verifica el estado del pulsador de encendido y
 * apagado de los LEDs (pulOnOff), y se actualiza el estado de la variable
 * ledActual en base al estado de los pulsadores de selección de LED
 * (pulNext y pulPrev). Luego, si el usuario ha presionado el pulsador
 * pulOnOff, se invierte el estado del LED actualmente seleccionado.
 *
 * Después, se actualiza la variable estadoPrevio con el valor leido del
 * pulsador pulOnOff y se llama al método mostarInformacionEnLcd para mostrar
 * la información en el LCD.
 */
void loop() {

  
  bool estadoPulOnOff = digitalRead(pulOnOff);
  byte ledActual = seleccionDeLed();

  if (estadoPulOnOff != estadoPrevio) {
    if (estadoPulOnOff == HIGH ) estadoDeLeds[ledActual - 1] = !estadoDeLeds[ledActual - 1];    
  }
  delay(10);

  estadoPrevio = estadoPulOnOff;

  mostarInformacionEnLcd(ledActual);
}

  /**
   * Devuelve el n  mero del LED actualmente seleccionado por el usuario.
   *
   * En este m todo se verifica el estado de los pulsadores de selección
   * de LED (pulNext y pulPrev) y se actualiza la variable ledActual en
   * base a los valores leidos. Si el usuario ha presionado el pulsador
   * pulNext, se incrementa en 1 la variable ledActual; si ha presionado
   * el pulsador pulPrev, se decrementa en 1 la variable ledActual.
   * Luego se actualiza la variable ledActual para que no sea mayor que 4
   * ni menor que 1, y se devuelve el valor actualizado.
   *
   * @return El n  mero del LED actualmente seleccionado.
   */
byte seleccionDeLed() {

  bool estadoPulNext = digitalRead(pulNext);
  bool estadoPulPrev = digitalRead(pulPrev);

  if (estadoPulNext != estadoPrevioPulNext or estadoPulPrev != estadoPrevioPulPrev) {
    estadoPulNext == HIGH && ledActual++;
    estadoPulPrev == HIGH && ledActual--;
  }

  delay(10);

  estadoPrevioPulNext = estadoPulNext;
  estadoPrevioPulPrev = estadoPulPrev;

  if (ledActual > 4) ledActual = 4;
  if (ledActual < 1) ledActual = 1;

  return ledActual;

}

/**
 * Muestra información en el LCD sobre el número de LED actual y su
 * estado, y actualiza el estado de los LEDs.
 *
 * @param ledActual El número del LED actualmente seleccionado.
 *
 * En este método se muestra en el LCD el número del LED actualmente
 * seleccionado y su estado. Luego, se actualiza el estado de cada LED
 * según su valor en el array estadoDeLeds.
 */
void mostarInformacionEnLcd(byte ledActual) {
  lcd.setCursor(0, 0);
  lcd.print("<PREV  L   NEXT>");
  lcd.setCursor(8, 0);
  lcd.print(ledActual);
  lcd.setCursor(0, 1);
  lcd.print("1:  2:  3:  4:  ");

  for (byte i = 0 ; i < sizeof(estadoDeLeds); i++ ) {
    byte valorSaltoLcd = (i * 2) * 2 + 2;
    lcd.setCursor(valorSaltoLcd, 1);
    lcd.print(estadoDeLeds[i]);
    digitalWrite(leds[i], estadoDeLeds[i]);
  }
  
  delay(10);
}
