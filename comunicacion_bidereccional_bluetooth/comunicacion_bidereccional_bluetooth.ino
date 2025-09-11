/* 

Comunicación serial bidireccional.

- Los datos recibidos bienen de una aplicacion creada en appInventor a travez de bluetooth

* Código escrito por: Esteban Carrillo para EDEPTEC. 
* Página web: https://www.edeptec.com
* Facebook: @edeptec
* Youtube: https://youtube.com/c/EDEPTEC

*/
#include <ArduinoJson.h>  // Libreria para convertir string a JSON
#include <SoftwareSerial.h>

#define rxPin 10
#define txPin 11

SoftwareSerial mySerial(rxPin, txPin);  // crear un nuevo onjeto SoftwareSerial

int leds[2] = { 13, 3 };       // Pines en donde van conectados los leds
int pulsadores[2] = { 2, 4 };  // Pines en donde van conectados los pulsadores

String str = "";  // Almacena el string recivido por el puerto serial

const int numeroDeDatos = 2;  // Numero de datos a recibir
int dato[numeroDeDatos];      // Array para almacenar los valores de los datos recibidos

bool estadoPrevio[2] = { 0, 0 };  //Estados previos de los pulsadores "Antirrebote"

/**
 * Configura los pines de los LEDs como salidas, de los pulsadores como entradas 
 * y establece la velocidad de comunicación serial.
 */
void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
  for (int i = 0; i < numeroDeDatos; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
    pinMode(pulsadores[i], INPUT_PULLUP);
  }
}

/**
 * Bucle principal del programa.
 *
 * En este bucle se verifica si hay datos disponibles en el puerto serie,
 * si es así se almacenan en un string y se convierten a un objeto JSON.
 * Luego se extraen los valores de los datos recibidos y se almacenan en un
 * array. Finalmente se actualiza el brillo de los LEDs con los valores
 * del array.
 */
void loop() {

  JsonDocument doc;  // Asigna el documento JSON a doc

  if (mySerial.available() > 0) {  // Verificar si hay datos disponibles
    // Leer hasta el final del string
    str = mySerial.readStringUntil('}');  //String en este punto {"value1":255,"value2":255,"value3":255

    // Agregar "}" al final del string
    str.concat("}");  //String en este punto: {"value1":255,"value2":255,"value3":255}

    //Serial.println(str);  // Imprime el string en el monitor serial
    DeserializationError error = deserializeJson(doc, str);  // Convertir el string a JSON

    if (error) {  // Verificar si hubo un error en la conversion
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }

    // Extrae los valores de los datos recibidos y los almacena en el array dato
    dato[0] = doc["Switch1"].as<boolean>();  //Valor del LED N°1
    dato[1] = doc["Switch2"].as<boolean>();  //Valor del LED N°2
  }

  bool estadoPulsador[2] = { 0, 0 };  // Almacena estados de los pulsadores

  for (int i = 0; i < numeroDeDatos; i++) {
    estadoPulsador[i] = digitalRead(pulsadores[i]);  // Estados lógicos del los pulsador

    if (estadoPulsador[i] != estadoPrevio[i] && estadoPulsador[i] == HIGH) {  // Implementación antirrebote && si se presiona el pulsador:

      dato[i] = !dato[i];                           // Hace un intercabio de valores ejemplo si antes era true ahora es false
      doc["Switch1"] = dato[0] ? "true" : "false";  //Establece le valor de "true" o "false" a la propiedad "Switch1" ejemplo {"Switch1":"true"}
      doc["Switch2"] = dato[1] ? "true" : "false";

      serializeJson(doc, mySerial);  // Convierte el json a string y lo envia a traves del puerto serial.
    }
    delay(10);                            // Pausa de 10ms
    estadoPrevio[i] = estadoPulsador[i];  //Implementacion Antirrebote

    digitalWrite(leds[i], dato[i]);  //Enciende o apaga los leds
  }
}