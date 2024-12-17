/*

  Código escrito por: Esteban Carrillo para EDEPTEC.
  Página web: https://www.edeptec.com
  Facebook: @edeptec
  Youtube: https://youtube.com/c/EDEPTEC

*/

#include <LiquidCrystal.h>
#include "DHT.h"

#define pulsadorSet A1 // Pulsador set en el pin A1
#define pulsadorMenos A2 // Pulsador menos en el pin A2
#define pulsadorMas A3 // Pulsador mas en el pin A3
#define calefactor 6 // Pin donde esta conectado el calefactor
#define ventilador 7 // Pin donde esta conectado el ventilador

#define DHTPIN 8     // Pin donde está conectado el sensor DHT

//#define DHTTYPE DHT11   // Descomentar si se usa el DHT 11
#define DHTTYPE DHT22   // Sensor DHT22

DHT dht(DHTPIN, DHTTYPE);

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // Pines del LCD

int temperaturaMinima = 10; // Variable para almacenar la temperatura minima
int temperaturaMaxima = 21; // Variable para almacenar la temperatura maxima
int temperaturaActual; // Variable para almacenar la temperatura actual

// Variables para almacenar el estado previo de los pulsadores
boolean estadoPrevioPulsadorSet = 0; 
boolean estadoPrevioPulsadorMas = 0; 
boolean estadoPrevioPulsadorMenos = 0;

/**
 * Configura los pines de los pulsadores como entradas, el pin del lcd como
 * salida y establece la velocidad de comunicación serial. Luego, inicializa
 * el lcd y el sensor DHT. Finalmente, establece los pines del calefactor y
 * ventilador como salidas y los pone en estado apagado.
 */
void setup() {

  Serial.begin(9600);
  lcd.begin(16, 2);
  dht.begin();
  pinMode(pulsadorSet, INPUT);
  pinMode(pulsadorMenos, INPUT);
  pinMode(pulsadorMas, INPUT);
  pinMode(calefactor, OUTPUT);
  pinMode(ventilador, OUTPUT);
  digitalWrite(calefactor, LOW);
  digitalWrite(ventilador, LOW);
  leerTemperaturaActual();
}


/**

  * Función principal de bucle que monitoriza y controla continuamente el sistema de clima.
  *
  * - Activa el calefactor si la temperatura actual está por debajo del umbral mínimo.
  * - Activa el ventilador si la temperatura actual está por encima del umbral máximo.
  * - Muestra las temperaturas mínima, actual y máxima en la pantalla LCD.
  *- Lee continuamente la temperatura actual y verifica la selección de temperatura. 

*/
void loop() {

  if (temperaturaActual <= temperaturaMinima) {
    digitalWrite(calefactor, HIGH);
    digitalWrite(ventilador, LOW);
  } else if (temperaturaActual >= temperaturaMaxima) {
    digitalWrite(calefactor, LOW);
    digitalWrite(ventilador, HIGH);
  } else {
    digitalWrite(ventilador, LOW);
    digitalWrite(calefactor, LOW);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T.min ");
  lcd.print("T.ac ");
  lcd.print("T.max");
  lcd.setCursor(0, 1);
  lcd.print(temperaturaMinima);
  lcd.print("oC  ");
  lcd.print(temperaturaActual);
  lcd.print("oC  ");
  lcd.print(temperaturaMaxima);
  lcd.print("oC");
  delay(100);

  for (int i = 0; i < 1000; i++) {
    
    leerTemperaturaActual();
    if (selectorDeTemperatura()) {
      setTemperaturaMinima();
      break;
    }
  }
}

/**
 * Lee la temperatura actual del sensor DHT y actualiza la variable
 * global temperaturaActual con el valor obtenido.
 */

void leerTemperaturaActual(){
  temperaturaActual = dht.readTemperature();
}

/**
 * Comprueba si se ha seleccionado una nueva temperatura mediante el pulsador set.
 * El pulsador set debe estar en el pin A1.
 *
 * @return true si se ha seleccionado una nueva temperatura, false en caso contrario.
 */
bool selectorDeTemperatura() {
  bool estadoPulsadorSet = digitalRead(pulsadorSet);
  bool cambiar = false;

  if (estadoPulsadorSet != estadoPrevioPulsadorSet && estadoPulsadorSet == HIGH) {
    cambiar = true;
  }
  delay(5);
  estadoPrevioPulsadorSet = estadoPulsadorSet;
  return cambiar;
}

/**
 * Aumenta la temperatura minima o maxima dependiendo de la temperatura seleccionada.
 *
 * @param temperatura El tipo de temperatura a aumentar, puede ser "minima" o
 *                    "maxima".
 *
 * @return true si se ha presionado el pulsador mas, false en caso contrario.
 */
bool aumentarTemperatura(String temperatura) {
  bool estadoPulsadorMas = digitalRead(pulsadorMas);
  if (estadoPulsadorMas != estadoPrevioPulsadorMas && estadoPulsadorMas == HIGH) {
    if (temperatura.equals("minima")) {
      temperaturaMinima++;
    } else if (temperatura.equals("maxima")) {
      temperaturaMaxima++;
    } else {
      return true;
    }
  }
  estadoPrevioPulsadorMas = estadoPulsadorMas;
}

/**
 * Disminuye la temperatura minima o maxima dependiendo de la temperatura seleccionada.
 *
 * @param temperatura El tipo de temperatura a disminuir, puede ser "minima" o
 *                    "maxima".
 */

void disminuirTemperatura(String temperatura) {
  bool estadoPulsadorMenos = digitalRead(pulsadorMenos);
  if (estadoPulsadorMenos != estadoPrevioPulsadorMenos && estadoPulsadorMenos == HIGH ) {
    if (temperatura.equals("minima")) {
      temperaturaMinima--;
    } else if (temperatura.equals("maxima")) {
      temperaturaMaxima--;
    }
  }
  estadoPrevioPulsadorMenos = estadoPulsadorMenos;
}

/**
 * Configura y permite el ajuste interactivo de la temperatura mínima.
 *
 * - Muestra el menú de selección de temperatura mínima en la pantalla LCD.
 * - Permite cambiar al ajuste de temperatura máxima si se selecciona.
 * - Incrementa o decrementa la temperatura mínima en función de los pulsadores.
 * - Asegura que la temperatura mínima esté dentro del rango de 0 a 16 grados.
 * - Actualiza la pantalla con la nueva temperatura mínima en tiempo real.
 */

void setTemperaturaMinima() {
  lcd.clear();

  for (int i = 0 ; i < 100; i++) {
    menuSeleccion("Tmin");

    if (selectorDeTemperatura()) {
      setTemperaturaMaxima();
      break;
    }
    delay(10);

    if (aumentarTemperatura("")) {
      delay(100 );

      while (!selectorDeTemperatura()) {
        aumentarTemperatura("minima");
        disminuirTemperatura("minima");
        temperaturaMinima = (temperaturaMinima < 0) ? temperaturaMinima = 0 : temperaturaMinima > 16 ? temperaturaMinima = 16 : temperaturaMinima;
        menuProgramarTemperatura("min");
      }
      break;
    }
  }

}

/**
 * Configura y permite el ajuste interactivo de la temperatura máxima.
 *
 * - Muestra el menú de selección de temperatura máxima en la pantalla LCD.
 * - Permite cambiar al ajuste de temperatura mínima si se selecciona.
 * - Incrementa o decrementa la temperatura máxima en función de los pulsadores.
 * - Asegura que la temperatura máxima esté dentro del rango de 20 a 30 grados.
 * - Actualiza la pantalla con la nueva temperatura máxima en tiempo real.
 */
void setTemperaturaMaxima() {
  lcd.clear();

  for (int i = 0 ; i < 100; i++) {
    menuSeleccion("Tmax");

    if (selectorDeTemperatura()) {
      setTemperaturaMinima();
      break;
    }

    delay(10);

    if (aumentarTemperatura("")) {
      delay(100);
      while (!selectorDeTemperatura()) {
        aumentarTemperatura("maxima");
        disminuirTemperatura("maxima");

        temperaturaMaxima = (temperaturaMaxima > 30) ? (temperaturaMaxima = 30) : (temperaturaMaxima < 20) ? (temperaturaMaxima = 20) : temperaturaMaxima;
        menuProgramarTemperatura("max");
      }
      break;
    }
  }
}
/**
 * Muestra el menú de programación de temperatura en la pantalla LCD.
 *
 * - Imprime "Set temp " seguido de "min" o "max" dependiendo del parámetro tipo.
 * - Imprime la temperatura actual en la segunda línea de la pantalla.
 * - Muestra la pantalla durante 100 milisegundos.
 *
 * @param tipo El tipo de temperatura a mostrar, puede ser "min" o "max".
 */
void menuProgramarTemperatura(String tipo) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Set temp ");
  lcd.print(tipo);
  lcd.setCursor(0, 1);
  lcd.print(tipo.equals("max") ? temperaturaMaxima : temperaturaMinima);
  lcd.print(" oC");
  delay(100);
}

/**
 * Muestra un menú de selección de temperatura en la pantalla LCD.
 *
 * - Imprime "Presione + para" en la primera línea de la pantalla.
 * - Imprime "Modificar " seguido de "min" o "max" dependiendo del parámetro tipo en la segunda línea.
 * - Muestra la pantalla durante 100 milisegundos.
 *
 * @param tipo El tipo de temperatura a mostrar, puede ser "Tmin" o "Tmax".
 */
void menuSeleccion(String tipo) {
  lcd.setCursor(0, 0);
  lcd.print("Presione + para");
  lcd.setCursor(0, 1);
  lcd.print("Modificar ");
  lcd.print(tipo);
}