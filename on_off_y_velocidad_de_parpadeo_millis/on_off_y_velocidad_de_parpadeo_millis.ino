/*

Encender / Apagar led y variar su velocidad de parpadeo usando millis().

* Código escrito por: Esteban Carrillo para EDEPTEC.
* Página web: https://www.edeptec.com
* Facebook: @edeptec
* Youtube: https://youtube.com/c/EDEPTEC

*/

#define botonResta 3  // Pulsador resta en el pin A0
#define botonSuma 4   // Pulsador suma en el pin A1
#define botonOnOff 5  // Pulsador on/off en el pin A2

#define led 2  // led en el pin 2

bool activarDesactivar = 0;       // Variable para controlar el estado del led
bool estadoAnteriorPulOnOff = 0;  // Variable para controlar el estado previo del pulsador on/off
int tiempo = 1000;                // Variable para controlar la velocidad de parpadeo

int tiempoMinimo = 50;    // Variable para controlar el tiempo minimo
int tiempoMaximo = 5000;  // Variable para controlar el tiempo maximo

unsigned long previousMillis = 0;
bool estadoDelLed = 0;


void setup() {
  Serial.begin(9600);
  pinMode(botonResta, INPUT_PULLUP);
  pinMode(botonSuma, INPUT_PULLUP);
  pinMode(botonOnOff, INPUT_PULLUP);
  pinMode(led, OUTPUT);
}

/**
 * Bucle principal del programa.
 *
 * En este bucle se verifica el estado del pulsador de
 * encendido y apagado del led (botonOnOff), y se
 * controla el estado del led (encendido o apagado)
 * y su velocidad de parpadeo.
 *
 * Se utiliza la funcion millis() para calcular el
 * tiempo de pausa entre parapadeos.
 *
 * Si el led esta apagado, se enciende. Si el led
 * esta encendido, se apaga. Luego se cambia el
 * estado del led y se actualiza su velocidad de
 * parpadeo.
 */

void loop() {

  while (encenderApagarLed()) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= manejarTiempo(&tiempo)) {
      previousMillis = currentMillis;

      if (estadoDelLed == 0) {
        estadoDelLed = 1;
      } else {
        estadoDelLed = 0;
      }
      digitalWrite(led, estadoDelLed);
    }
  }
  digitalWrite(led, 0);
}

/**
 * Comprueba el estado del pulsador on/off y actualiza la variable
 * activarDesactivar.
 *
 * @return true si el led debe estar encendido, false en caso contrario.
 */
bool encenderApagarLed() {
  bool estadoBotonOnOff = digitalRead(botonOnOff);
  (estadoBotonOnOff != estadoAnteriorPulOnOff && estadoBotonOnOff) && (activarDesactivar = !activarDesactivar);
  estadoAnteriorPulOnOff = estadoBotonOnOff;

  delay(1);
  return activarDesactivar;
}

/**
 * Ajusta el valor de la variable tiempo en función del estado de los
 * pulsadores suma y resta.
 *
 * Si el pulsador suma se encuentra en estado HIGH, se incrementa el valor
 * de tiempo en 10 milisegundos y se produce un delay de 10 milisegundos.
 *
 * Si el pulsador resta se encuentra en estado HIGH, se decrementa el valor
 * de tiempo en 10 milisegundos y se produce un delay de 10 milisegundos.
 *
 * Se asegura de que el valor de tiempo no sea menor que tiempoMinimo ni
 * mayor que tiempoMaximo.
 *
 * @param tiempo Puntero a la variable que almacena el valor de tiempo.
 * @return El valor ajustado de la variable tiempo.
 */
int manejarTiempo(int *tiempo) {
  if (digitalRead(botonSuma)) {
    *tiempo = *tiempo + 10;
    delay(10);
  }
  if (digitalRead(botonResta)) {
    *tiempo = *tiempo - 10;
    delay(10);
  }
  *tiempo = (*tiempo < tiempoMinimo)
              ? tiempoMinimo
            : (*tiempo > tiempoMaximo)
              ? tiempoMaximo
              : *tiempo;

  return *tiempo;
}