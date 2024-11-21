/* 

* Código escrito por: Esteban Carrillo para EDEPTEC. 
* Página web: https://www.edeptec.com
* Facebook: @edeptec
* Youtube: https://youtube.com/c/EDEPTEC

*/

/* Definimos los pines en donde van conectados los pulsadores */
#define pulCambio A0
#define pulSuma A1
#define pulResta A2

byte ledPins[] = {3, 5, 6, 9}; // Pines en donde van conectados los leds
byte numeroDeLeds =  sizeof(ledPins); // Número de leds en el array
byte pwmLeds[sizeof(ledPins)]; // Array para almacenar el valor del pwm de cada led
bool estadoPrevio = 0; // Variable para controlar el estado previo del pulsador

int pwm; // Variable para almacenar el valor del pwm
int x;  // Variable para controlar el led actual

void setup() {
  //--- Declaramos entradas y salidas ---//
  pinMode(pulCambio, INPUT);
  pinMode(pulSuma, INPUT);
  pinMode(pulResta, INPUT);
  /* Configuramos los pines de los leds como salidas */
  for (byte x = 0 ; x < numeroDeLeds; x++) {
    pinMode(ledPins[x], OUTPUT);
  }
}

void loop() {

  bool estadoPulCambio = digitalRead(pulCambio); // Estado lógico del pulsador

  if (estadoPulCambio != estadoPrevio) { // Implementación antirrebote
    if (estadoPulCambio == HIGH) { // Cuando el pulsador de cambio de led se presione
      x++; // Cambiamos de led
      if (x == numeroDeLeds) x = 0; // Si llegamos al último led, volvemos al primero
      pwm = pwmLeds[x]; // Obtenemos el valor del pwm del led actual y lo almacenamos en la variable pwm
    }
    delay(10); // Pausa de 10ms
  }

  estadoPrevio = estadoPulCambio; // Implementación antirrebote

  (digitalRead(pulSuma) == HIGH) && pwm++; // Si presionamos el pulsador de suma, sumamos el valor de la variable pwm
  (digitalRead(pulResta) == HIGH) && pwm--; // Si presionamos el pulsador de resta, restamos el valor de la variable pwm
  // Limitamos el valor de la variable pwm
  if (pwm > 255) pwm = 255;
  if (pwm < 0) pwm = 0;

  pwmLeds[x] = pwm; // Almacenamos el valor de la variable pwm en la posicion del array perteneciente al led actual

  analogWrite(ledPins[x], pwmLeds[x]); // Enviamos por el pin en donde esta conectado el led, el valor del pwm que le pertenece
}