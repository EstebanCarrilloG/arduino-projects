/* 

* Código escrito por: Esteban Carrillo para EDEPTEC. 
* Página web: https://www.edeptec.com
* Facebook: @edeptec
* Youtube: https://youtube.com/c/EDEPTEC

*/
#include <ArduinoJson.h>  // Libreria para convertir string a JSON

String str = "";

/**
 * Configura los pines de los LEDs como salidas y establece la velocidad de
 * comunicación serial.
 */
void setup() {
  Serial.begin(9600);
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
    str = Serial.readStringUntil('}');

    //String en este punto {"value1":255,"value2":255,"value3":255

    str.concat("}");  // Agregar "}" al final del string

    //String en este punto: {"value1":255,"value2":255,"value3":255}

    Serial.println(str);  // Imprime el string en el monitor serial

    DeserializationError error = deserializeJson(doc, str);  // Convertir el string a JSON

    if (error) {  // Verificar si hubo un error en la conversion
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }

    bool switch1State = doc["Switch1"].as<bool>();
    bool switch2State = doc["Switch2"].as<bool>();

    (switch1State) ? Serial.println("S1: On") : Serial.println("S1: Off");
    (switch2State) ? Serial.println("S2: On") : Serial.println("S2: Off");

    int slider1Value = doc["slider1"].as<int>();
    int slider2Value = doc["slider2"].as<int>();

    if (slider1Value) {
      Serial.print("Slider 1 Value: ");
      Serial.println(slider1Value);
    }

    if (slider2Value) {
      Serial.print("Slider 2 Value: ");
      Serial.println(slider2Value);
    }

    String text = doc["text"].as<String>();

    if(!text.equals("")){
      Serial.print("Text: ");
      Serial.println(text);
    }
  }
}
