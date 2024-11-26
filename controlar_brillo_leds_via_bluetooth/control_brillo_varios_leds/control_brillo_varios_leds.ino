/* 

* Código escrito por: Esteban Carrillo para EDEPTEC. 
* Página web: https://www.edeptec.com
* Facebook: @edeptec
* Youtube: https://youtube.com/c/EDEPTEC

*/
#include <ArduinoJson.h>  // Libreria para convertir string a JSON

int leds[3] = { 5, 6, 9 };  // Pines en donde van conectados los leds/

String str = "";
const int numeroDeDatos = 3;  // Numero de datos a recibir
int datos[numeroDeDatos];     // Array para almacenar los valores de los datos recibidos

/**
 * Configura los pines de los LEDs como salidas y establece la velocidad de
 * comunicación serial.
 */
void setup() {
  Serial.begin(9600);
  for (int i = 0; i < numeroDeDatos; i++) {
    pinMode(leds[i], OUTPUT);
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
  JsonDocument doc;          // Asigna el documento JSON a doc
  if (Serial.available()) {  // Verificar si hay datos disponibles


    // Leer hasta el final del string
    str = Serial.readStringUntil('}');  //String en este punto {"value1":255,"value2":255,"value3":255

    // Agregar "}" al final del string
    str.concat("}");  //String en este punto: {"value1":255,"value2":255,"value3":255}

    Serial.println(str);  // Imprime el string en el monitor serial

    DeserializationError error = deserializeJson(doc, str);  // Convertir el string a JSON

    if (error) {  // Verificar si hubo un error en la conversion
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }

    // Extrae los valores de los datos recibidos y los almacena en el array dato
    datos[0] = doc["value1"].as<int>();
    datos[1] = doc["value2"].as<int>();
    datos[2] = doc["value3"].as<int>();
  }

  // Actualizar el brillo de los LEDs
  for (int i = 0; i < numeroDeDatos; i++) {
    analogWrite(leds[i], datos[i]);
  }
}
